/**
* @author Steven Goldade
* @date 9/11/2023
*/
#pragma once
#include "low_level.h"
#include "nmi_ppu_buffer.h"
#include "palette.h"
#include <type_traits>

extern "C" void __nmi_update();
extern "C" LEAF void ppu_background_update();

namespace nespp {
    union PpuControlRegister {
        struct {
            u8 nametable : 2;
            bool vram_increment : 1;
            u8 sprite_pattern_table : 1;
            u8 background_pattern_table : 1;
            bool sprite_size : 1;
            bool ppu_master_slave : 1;
            bool vblank_nmi : 1;
        };
        u8 value;
        
        auto constexpr operator=(const PpuControlRegister& other) volatile noexcept -> volatile PpuControlRegister& {
            value = other.value;
            return *this;
        }
    };

    union PpuMaskRegister {
        struct {
            bool grayscale : 1;
            bool render_left8_background : 1;
            bool render_left8_sprites : 1;
            bool show_background : 1;
            bool show_sprites : 1;
            bool emphasize_red : 1;
            bool emphasize_green : 1;
            bool emphasize_blue : 1;
        };
        u8 value;
        
        auto constexpr operator=(const PpuMaskRegister& other) volatile noexcept -> volatile PpuMaskRegister& {
            value = other.value;
            return *this;
        }
    };

    union PpuStatusRegister {
        struct {
            u8 open_bus : 5;
            bool sprite_overflow : 1;
            bool sprite_0_hit : 1;
            bool vblank_started : 1;
        };
        u8 value;
    };

    template<u16 ADDRESS>
    struct PpuOamRegister {
        WriteOnly<u8, ADDRESS> address;
        u8 data;
    };

    template<u16 ADDRESS>
    struct PpuVramRegister {
        WriteOnly<u8, ADDRESS> address;
        u8 data;
    };
    
    enum class Nametable : u8 {
        _0 = 0,
        _1 = 1,
        _2 = 2,
        _3 = 3
    };
    
    struct PpuNametable {
        union {
            u8 tile_yx[30][32];
            u8 tile[960];
        };
    };
    
    struct PpuAttributeCell {
        union {
            struct {
                u8 top_left : 2;
                u8 top_right : 2;
                u8 bottom_left : 2;
                u8 bottom_right : 2;
            };
            u8 value;
        };
        
        auto constexpr set(u8 x, u8 y, u8 value) noexcept -> void {
            x ? y ? bottom_right = value : top_right = value : y ? bottom_left = value : top_left = value;
        }
    };
    
    struct PpuAttributeTable {
        union {
            PpuAttributeCell value_yx[8][8];
            PpuAttributeCell value[64];
        };
    };
    
    struct PpuSprite {
        u8 y;
        u8 tile_number;
        struct {
            u8 palette : 2;
            u8 UNUSED : 3;
            bool behind_background : 1;
            bool horizontal_flip : 1;
            bool vertical_flip : 1;
        };
        u8 x;
        
        auto constexpr hide() noexcept -> void {
            y = 255;
        }
    };
    
    template<class T>
    concept VramMirrorAccessor = requires(T a, T::wrapped_type b, u16 length, u16 offset) {
        std::is_assignable_v<T, typename T::wrapped_type>;
        a = b;
        a.write();
        a.read();
        a.write_partial(length, offset);
        a.read_partial(length, offset);
    };
    
    template<class T>
    concept VramAccessor = requires(T a, T::wrapped_type b, u8* data, u16 length, u16 offset, u8 x, u8 y) {
        a.write_partial(data, length, offset);
        a.write_partial(data, length, x, y);
        a.write_partial(b, length, offset);
        a.write(b);
        a.read_partial(data, length, offset);
        a.read_partial(data, length, x, y);
        a.read_partial(b, length, offset);
        a.read(b);
        a.address();
        { a.cpu_copy() } -> VramMirrorAccessor;
    };
    
    struct Ppu {
        Ppu() = delete;
        ~Ppu() = delete;

        static constexpr u16 PPUCTRL = 0x2000;
        auto static constexpr control() noexcept -> WriteOnly<PpuControlRegister, PPUCTRL> {
            return {};
        }

        static constexpr u16 PPUMASK = 0x2001;
        auto static constexpr mask() noexcept -> WriteOnly<PpuMaskRegister, PPUMASK> {
            return {};
        }

        static constexpr u16 PPUSTATUS = 0x2002;
        auto static constexpr status() noexcept -> const volatile PpuStatusRegister& {
            return read_only_memory<PpuStatusRegister>(PPUSTATUS);
        }

        static constexpr u16 OAMADDR = 0x2003;
        static constexpr u16 OAMDATA = 0x2004;
        [[nodiscard]] auto static constexpr oam() noexcept -> volatile PpuOamRegister<OAMADDR>& {
            return memory<PpuOamRegister<OAMADDR>>(OAMADDR);
        }

        static constexpr u16 PPUSCROLL = 0x2005;
        [[nodiscard]] auto static constexpr scroll() noexcept -> volatile u8& {
            return memory<u8>(PPUSCROLL);
        }

        static constexpr u16 PPUADDR = 0x2006;
        static constexpr u16 PPUDATA = 0x2007;
        [[nodiscard]] auto static constexpr vram() noexcept -> volatile PpuVramRegister<PPUADDR>& {
            return memory<PpuVramRegister<PPUADDR>>(PPUADDR);
        }

        static constexpr u16 OAMDMA = 0x4014;
        [[nodiscard]] auto static constexpr oam_dma() noexcept -> volatile u8& {
            return memory<u8>(OAMDMA);
        }

        /**
         * Writes to the VRAM on the PPU.
         *
         * @param address the address on the PPU to write to
         * @param data a pointer to the data to write
         * @param length the length of data to write
         * @return
         */
        auto static constexpr vram_write(const u16 address, const u8* data, const u16 length) noexcept -> void {
            vram().address = address >> 8;
            vram().address = address & 0xFF;
            for(u16 i = 0; i < length; ++i) {
                vram().data = data[i];
            }
        }

        /**
         * Reads data from the VRAM on the PPU to the supplied buffer.
         * Caller must ensure the buffer is of sufficient size.
         *
         * @param address the address on the PPU to read from
         * @param data a pointer to the buffer the data will be read to. Ensure the buffer is of sufficient size
         * @param length the length of the data to read
         * @return
         */
        auto static constexpr vram_read(const u16 address, u8* data, const u16 length) noexcept -> void {
            vram().address = address >> 8;
            vram().address = address & 0xFF;
            
            // internal read buffer garbage data
            if(address < 0x3F00) (void)vram().data;
            
            for(u16 i = 0; i < length; ++i) {
                data[i] = vram().data;
            }
        }

        /**
         * A template struct that wraps the an object with methods to read and write that object
         * in PPU VRAM. As it extends the type, it also creates a copy of this memory on the CPU side.
         *
         * @tparam T the type of the object represented in VRAM. sizeof(T) must be less than 255
         * @tparam ADDRESS the address in VRAM the object lives at
         */
        template <class T, u16 ADDRESS>
        struct UnbufferedVramMirrorAccessor : T {
            using wrapped_type = T;
            constexpr UnbufferedVramMirrorAccessor() = default;
            
            auto constexpr operator=(T& other) noexcept -> UnbufferedVramMirrorAccessor& {
                T::operator=(other);
                return *this;
            }
        
            auto constexpr operator=(T&& other) noexcept -> UnbufferedVramMirrorAccessor&{
                T::operator=(other);
                return *this;
            }
            
            auto constexpr write_partial(u16 length, u16 offset) const noexcept -> void {
                vram_write(ADDRESS+offset, bit_cast<u8*>(this)+offset, length);
            }
            
            auto constexpr write() const noexcept -> void {
                write_partial(sizeof(T), 0);
            }
            
            auto constexpr read_partial(u16 length, u16 offset) noexcept -> void {
                vram_read(ADDRESS+offset, bit_cast<u8*>(this)+offset, length);
            }
            
            auto constexpr read() noexcept -> void {
                read_partial(sizeof(T), 0);
            }
            
            [[nodiscard]] auto constexpr address() const noexcept -> u16 {
                return ADDRESS;
            }
        };
        static_assert(VramMirrorAccessor<UnbufferedVramMirrorAccessor<PpuNametable, 0>>);

        /**
         * A template struct that indicates the provided type exists only in VRAM.
         * The CPU will have no copy of the object. If one is needed, the class
         * used should be the plain VRAM class. <br/>
         *
         * @tparam T the type of the object represented in VRAM
         * @tparam ADDRESS the address in VRAM the object lives at
         * @tparam STRIDE the distance in bytes 1 unit of "Y" represents for this object if applicable
         */
        template <class T, u16 ADDRESS, u16 STRIDE = 1>
        struct UnbufferedVramAccessor {
            using wrapped_type = T;
            constexpr UnbufferedVramAccessor() = default;
            
            auto constexpr write_partial(const u8* data, u16 length, u16 offset) const noexcept -> void {
                vram_write(ADDRESS+offset, data, length);
            };
            
            auto constexpr write_partial(const u8* data, const u16 length, const u8 x, const u8 y) const noexcept -> void {
                write_partial(data, length, y*STRIDE + x);
            }

            auto constexpr write_partial(const T& value, const u16 length, const u16 offset) const noexcept -> void {
                write_partial(bit_cast<u8*>(&value) + offset, length, offset);
            }

            auto constexpr write(const T& value) const noexcept -> void {
                write_partial(bit_cast<u8*>(&value), sizeof(T), 0);
            }
        
            auto constexpr read_partial(u8* data, u16 length, u16 offset) const noexcept -> void {
                vram_read(ADDRESS+offset, data, length);
            };

            auto constexpr read_partial(const u8* data, const u16 length, const u8 x, const u8 y) const noexcept -> void {
                read_partial(data, length, y*STRIDE + x);
            }

            auto constexpr read_partial(T& value, const u16 length, const u16 offset) const noexcept -> void {
                read_partial(bit_cast<u8*>(&value)+offset, length, offset);
            }

            auto constexpr read(T& value) const noexcept -> void {
                read_partial(bit_cast<u8*>(&value), 0, sizeof(T));
            }

            [[nodiscard]] auto constexpr address() const noexcept -> u16 {
                return ADDRESS;
            }
            
            [[nodiscard]] auto constexpr cpu_copy() const noexcept -> UnbufferedVramMirrorAccessor<T, ADDRESS> {
                return UnbufferedVramMirrorAccessor<T, ADDRESS>();
            };
        };
        static_assert(VramAccessor<UnbufferedVramAccessor<PpuNametable,0>>);

        static UnbufferedVramAccessor<PpuNametable, 0x2000, 32> nametable_0;
        static UnbufferedVramAccessor<PpuAttributeTable, 0x23C0, 8> attribute_table_0;
        static UnbufferedVramAccessor<PpuNametable, 0x2400, 32> nametable_1;
        static UnbufferedVramAccessor<PpuAttributeTable, 0x27C0, 8> attribute_table_1;
        static UnbufferedVramAccessor<PpuNametable, 0x2800, 32> nametable_2;
        static UnbufferedVramAccessor<PpuAttributeTable, 0x2BC0, 8> attribute_table_2;
        static UnbufferedVramAccessor<PpuNametable, 0x2C00, 32> nametable_3;
        static UnbufferedVramAccessor<PpuAttributeTable, 0x2FC0, 8> attribute_table_3;
        static UnbufferedVramAccessor<Palette, 0x3F00> background_palette;
        static UnbufferedVramAccessor<Palette, 0x3F10> sprite_palette;

        auto static get_frame_count() -> u8;

        auto static is_rendering() -> bool;

        /**
         * Waits until the frame counter increases before returning.
         * The frame counter will increase during the NMI update.
         */
        auto static wait() -> void;

        auto static constexpr wait_vblank() noexcept -> void {
            while(!status().vblank_started);
        }

        /**
         * Clears the sprites from the screen by moving all of them off screen.
         */
        auto static constexpr clear_sprites() noexcept -> void {
            for(auto & sprite : sprites) {
                sprite.hide();
            }
        }
        
        static PpuSprite sprites[64];
    private:
        friend void ::__nmi_update();
        static volatile u8 frame_count;

        /**
         * Background update that performs all the currently buffered actions
         * for the PPU, including data transfer and update to the control and mask registers.
         *
         * This will always be called during the vertical blank NMI, but can be manually called earlier to force
         * an immediate change.
         */
        auto static background_update() -> void;
        
        struct Initializer {
            Initializer();
        };
        static Initializer init;
    };

    struct BufferedPpu {
        /**
         * A template struct that wraps the an object with methods to read and write that object
         * in PPU VRAM. As it extends the type, it also creates a copy of this memory on the CPU side.
         *
         * @tparam T the type of the object represented in VRAM. sizeof(T) must be less than 255
         * @tparam ADDRESS the address in VRAM the object lives at
         */
        template <class T, u16 ADDRESS>
        struct BufferedVramMirrorAccessor : T {
            using wrapped_type = T;
            constexpr BufferedVramMirrorAccessor() = default;
            
            auto constexpr operator=(T& other) noexcept -> BufferedVramMirrorAccessor& {
                T::operator=(other);
                return *this;
            }
        
            auto constexpr operator=(T&& other) noexcept -> BufferedVramMirrorAccessor&{
                T::operator=(other);
                return *this;
            }
            
            auto constexpr write_partial(u16 length, u16 offset) const noexcept -> void {
                vram_write(ADDRESS+offset, bit_cast<u8*>(this)+offset, length);
            }
            
            auto constexpr write() const noexcept -> void {
                write_partial(sizeof(T), 0);
            }
            
            auto constexpr read_partial(u16 length, u16 offset) noexcept -> void {
                // NO OP
                (void)length;
                (void)offset;
            }
            
            auto constexpr read() noexcept -> void {
                read_partial(sizeof(T), 0);
            }
            
            [[nodiscard]] auto constexpr address() const noexcept -> u16 {
                return ADDRESS;
            }
        };
        static_assert(VramMirrorAccessor<BufferedVramMirrorAccessor<PpuNametable, 0>>);
        
        /**
         * A template struct that indicates the provided type exists only in VRAM.
         * The CPU will have no copy of the object. If one is needed, the class
         * used should be the plain VRAM class. <br/>
         *
         * @tparam T the type of the object represented in VRAM
         * @tparam ADDRESS the address in VRAM the object lives at
         * @tparam STRIDE the distance in bytes 1 unit of "Y" represents for this object if applicable
         */
        template <class T, u16 ADDRESS, u16 STRIDE = 1>
        struct BufferedVramAccessor {
            using wrapped_type = T;
            constexpr BufferedVramAccessor() = default;
            
            auto constexpr write_partial(const u8* data, u16 length, u16 offset) const noexcept -> void {
                NMI_PPU_Buffer::write_buffer(ADDRESS+offset, data, length);
            };
            
            auto constexpr write_partial(const u8* data, const u16 length, const u8 x, const u8 y) const noexcept -> void {
                write_partial(data, length, y*STRIDE + x);
            }

            auto constexpr write_partial(const T& value, const u16 length, const u16 offset) const noexcept -> void {
                write_partial(bit_cast<u8*>(&value) + offset, length, offset);
            }

            auto constexpr write(const T& value) const noexcept -> void {
                write_partial(bit_cast<u8*>(&value), sizeof(T), 0);
            }
        
            auto constexpr read_partial(const u8* data, u16 length, u16 offset) const noexcept -> void {
                // NO OP
                (void)data;
                (void)length;
                (void)offset;
            };

            auto constexpr read_partial(const u8* data, const u16 length, const u8 x, const u8 y) const noexcept -> void {
                read_partial(data, length, y*STRIDE + x);
            }

            auto constexpr read_partial(T& value, const u16 length, const u16 offset) const noexcept -> void {
                read_partial(bit_cast<u8*>(&value)+offset, length, offset);
            }

            auto constexpr read(T& value) const noexcept -> void {
                read_partial(bit_cast<u8*>(&value), 0, sizeof(T));
            }

            [[nodiscard]] auto constexpr address() const noexcept -> u16 {
                return ADDRESS;
            }
            
            [[nodiscard]] auto constexpr cpu_copy() const noexcept -> BufferedVramMirrorAccessor<T, ADDRESS> {
                return Unbuffered_VRAM_Mirror_Accessor<T, ADDRESS>();
            };
        };
        static_assert(VramAccessor<BufferedVramAccessor<PpuNametable,0>>);
        
        static BufferedVramAccessor<PpuNametable, 0x2000, 32> nametable_0;
        static BufferedVramAccessor<PpuAttributeTable, 0x23C0, 8> attribute_table_0;
        static BufferedVramAccessor<PpuNametable, 0x2400, 32> nametable_1;
        static BufferedVramAccessor<PpuAttributeTable, 0x27C0, 8> attribute_table_1;
        static BufferedVramAccessor<PpuNametable, 0x2800, 32> nametable_2;
        static BufferedVramAccessor<PpuAttributeTable, 0x2BC0, 8> attribute_table_2;
        static BufferedVramAccessor<PpuNametable, 0x2C00, 32> nametable_3;
        static BufferedVramAccessor<PpuAttributeTable, 0x2FC0, 8> attribute_table_3;
        static BufferedVramAccessor<Palette, 0x3F00> background_palette;
        static BufferedVramAccessor<Palette, 0x3F10> sprite_palette;
        
        auto static constexpr on() -> void {
            mask.show_background = true;
            mask.show_sprites = true;
        }

        auto static constexpr off() -> void {
            mask.show_background = false;
            mask.show_sprites = false;
        }
        
        static PpuControlRegister& control;
        static PpuMaskRegister& mask;
        static u8& scroll_x;
        static u8& scroll_y;
    private:
    };
}// namespace nespp
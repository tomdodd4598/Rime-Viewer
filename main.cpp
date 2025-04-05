#include <array>
#include <cstddef>
#include <iostream>

// All colors
enum class Color { WHITE, YELLOW, MAGENTA, BLUE, CYAN, GREEN };

static char const* to_string(Color color) {
    switch (color) {
    case Color::WHITE:
        return "White";
    case Color::YELLOW:
        return "Yellow";
    case Color::MAGENTA:
        return "Magenta";
    case Color::BLUE:
        return "Blue";
    case Color::CYAN:
        return "Cyan";
    case Color::GREEN:
        return "Green";
    }
}

// Colors must be in order
#define COLOR_ORDER0(X1, X2, X3, X4) std::array<Color, 4>{ X1, X2, X3, X4 }, std::array<Color, 4>{ X4, X3, X2, X1 }
#define COLOR_ORDER(X1, X2, X3, X4) COLOR_ORDER0(static_cast<Color>(X1), static_cast<Color>(X2), static_cast<Color>(X3), static_cast<Color>(X4))

constexpr std::array<std::array<Color, 4>, 30> COLOR_ORDERS = {
    COLOR_ORDER(0, 1, 2, 3),
    COLOR_ORDER(0, 1, 2, 4),
    COLOR_ORDER(0, 1, 2, 5),
    COLOR_ORDER(0, 1, 3, 4),
    COLOR_ORDER(0, 1, 3, 5),
    COLOR_ORDER(0, 1, 4, 5),
    COLOR_ORDER(0, 2, 3, 4),
    COLOR_ORDER(0, 2, 3, 5),
    COLOR_ORDER(0, 2, 4, 5),
    COLOR_ORDER(0, 3, 4, 5),
    COLOR_ORDER(1, 2, 3, 4),
    COLOR_ORDER(1, 2, 3, 5),
    COLOR_ORDER(1, 2, 4, 5),
    COLOR_ORDER(1, 3, 4, 5),
    COLOR_ORDER(2, 3, 4, 5),
};

// All iris sizes
enum class Size { SMALL, MEDIUM, LARGE };

static char const* to_string(Size size) {
    switch (size) {
    case Size::SMALL:
        return "Small";
    case Size::MEDIUM:
        return "Medium";
    case Size::LARGE:
        return "Large";
    }
}

#define SIZE_ORDER(X1, X2, X3, X4) std::array<Size, 4>{ static_cast<Size>(X1), static_cast<Size>(X2), static_cast<Size>(X3), static_cast<Size>(X4) }

// Sizes must not repeat
constexpr std::array<std::array<Size, 4>, 8> SIZE_ORDERS = {
    SIZE_ORDER(0, 1, 0, 2),
    SIZE_ORDER(0, 2, 0, 2),
    SIZE_ORDER(0, 2, 1, 2),
    SIZE_ORDER(1, 0, 1, 2),
    SIZE_ORDER(1, 2, 0, 2),
    SIZE_ORDER(1, 2, 1, 2),
    SIZE_ORDER(2, 0, 1, 2),
    SIZE_ORDER(2, 1, 0, 2),
};

#define POSITION_OFFSET(X1, X2, X3, X4) std::array<int, 4>{ X1, X2, X3, X4 }

// Separations at least 3, total distance at most 11
constexpr std::array<std::array<int, 4>, 10> POSITION_OFFSETS = {
    POSITION_OFFSET(0, 3, 6, 9),
    POSITION_OFFSET(0, 3, 6, 10),
    POSITION_OFFSET(0, 3, 6, 11),
    POSITION_OFFSET(0, 3, 7, 10),
    POSITION_OFFSET(0, 3, 7, 11),
    POSITION_OFFSET(0, 3, 8, 11),
    POSITION_OFFSET(0, 4, 7, 10),
    POSITION_OFFSET(0, 4, 7, 11),
    POSITION_OFFSET(0, 4, 8, 11),
    POSITION_OFFSET(0, 5, 8, 11),
};

int main() {
    int solution_count = 0;

    // All position offsets
    for (auto const& offset : POSITION_OFFSETS) {
        // All positions
        for (int i = 0, top = 20 - offset[3]; i <= top; ++i) {
            std::array<int, 4> positions{ i + offset[0], i + offset[1], i + offset[2], i + offset[3] };

            // All color orders
            for (auto const& colors : COLOR_ORDERS) {
                // All size orders
                for (auto const& sizes : SIZE_ORDERS) {
                    bool valid = true;

                    for (std::size_t j = 0; j < 4; ++j) {
                        // Green color must use small size
                        if (colors[j] == Color::GREEN && sizes[j] != Size::SMALL) {
                            valid = false;
                            break;
                        }

                        // Small size must have equal separations either side
                        if ((j == 1 || j == 2) && sizes[j - 1] == Size::SMALL && sizes[j + 1] == Size::SMALL && 2 * positions[j] != positions[j - 1] + positions[j + 1]) {
                            valid = false;
                            break;
                        }
                    }

                    if (!valid) {
                        continue;
                    }

                    auto print_solution = [&] {
                        std::cout << '[';
                        for (std::size_t j = 0; j < 4; ++j) {
                            if (j > 0) {
                                std::cout << ", ";
                            }
                            std::cout << '(' << to_string(colors[j]) << ", " << to_string(sizes[j]) << ", " << positions[j] << ')';
                        }
                        std::cout << ']' << std::endl;
                    };

                    // Riven
                    if (colors[3] == Color::YELLOW && colors[2] == Color::BLUE && positions[2] == 12 && sizes[1] == Size::MEDIUM && positions[0] == 4) {
                        std::cout << "Riven solution:\n";
                        print_solution();
                    }

                    ++solution_count;
                }
            }
        }
    }

    std::cout << "\nTotal solutions: " << solution_count << std::endl;

    return 0;
}

#include <iostream>

int main() {

    int width, height;

    std::cout << "Input width: ";
    std::cin >> width;
    std::cout << "Input height: ";
    std::cin >> height;

    std::cout << "Shape: " << std::endl;

    for (int h = 0; h < height; h++){ 
        for (int w = 0; w < width; w++){
            std::cout << "*"; 
        }
        std::cout << "\n";
    }

    return 0;

}

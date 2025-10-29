#include <iostream>
#include <string>
#include <limits>
#include "../lib/Display/display.h"
#include "../lib/Weather/weather.h"

void clearScreen() {
    // Multiplataforma: imprime líneas para "limpiar" la pantalla
    std::cout << std::string(50, '\n');
}

void showMenu() {
    std::cout << "\n========================================\n";
    std::cout << "     SISTEMA DE MONITOREO DE CLIMA     \n";
    std::cout << "========================================\n";
    std::cout << "1. Actualizar temperatura\n";
    std::cout << "2. Actualizar presión\n";
    std::cout << "3. Actualizar ambos\n";
    std::cout << "4. Mostrar valores actuales\n";
    std::cout << "5. Agregar nuevo display\n";
    std::cout << "q. Salir\n";
    std::cout << "========================================\n";
    std::cout << "Opción: ";
}

int main() {
    Weather weather;
    int displayCount = 0;
    
    // Crear algunos displays iniciales
    auto display1 = std::make_shared<Display>(&weather);
    auto display2 = std::make_shared<Display>(&weather);
    
    weather.addDisplay(display1);
    weather.addDisplay(display2);
    displayCount = 2;
    
    std::cout << "Sistema iniciado con " << displayCount << " displays.\n";
    
    std::string option;
    double newTemp, newPressure;
    
    while (true) {
        showMenu();
        std::cin >> option;
        
        // Limpiar el buffer de entrada
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (option == "q" || option == "Q") {
            std::cout << "\n¡Saliendo del sistema! Hasta luego.\n";
            break;
        }
        
        if (option == "1") {
            std::cout << "\nIngrese nueva temperatura (°C): ";
            if (std::cin >> newTemp) {
                std::cout << "\n--- Actualizando temperatura ---\n";
                weather.setTemperature(newTemp);
            } else {
                std::cout << "Error: Valor inválido.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else if (option == "2") {
            std::cout << "\nIngrese nueva presión (hPa): ";
            if (std::cin >> newPressure) {
                std::cout << "\n--- Actualizando presión ---\n";
                weather.setPressure(newPressure);
            } else {
                std::cout << "Error: Valor inválido.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else if (option == "3") {
            std::cout << "\nIngrese nueva temperatura (°C): ";
            if (std::cin >> newTemp) {
                std::cout << "Ingrese nueva presión (hPa): ";
                if (std::cin >> newPressure) {
                    std::cout << "\n--- Actualizando temperatura y presión ---\n";
                    weather.setTemperature(newTemp);
                    weather.setPressure(newPressure);
                } else {
                    std::cout << "Error: Valor de presión inválido.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } else {
                std::cout << "Error: Valor de temperatura inválido.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else if (option == "4") {
            std::cout << "\n--- VALORES ACTUALES ---\n";
            std::cout << "Temperatura: " << weather.getTemperature() << " °C\n";
            std::cout << "Presión: " << weather.getPressure() << " hPa\n";
            std::cout << "Displays activos: " << displayCount << "\n";
        }
        else if (option == "5") {
            auto newDisplay = std::make_shared<Display>(&weather);
            weather.addDisplay(newDisplay);
            displayCount++;
            std::cout << "\n✓ Nuevo display agregado. Total: " << displayCount << " displays.\n";
            
            // Notificar al nuevo display con los valores actuales
            std::cout << "\n--- Sincronizando nuevo display ---\n";
            weather.notifyDisplays();
        }
        else {
            std::cout << "\nOpción inválida. Intente nuevamente.\n";
        }
        
        std::cout << "\nPresione Enter para continuar...";
        std::cin.get();
    }
    
    return 0;
}
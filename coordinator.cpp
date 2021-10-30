#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "coordfunc.h"
#include "iofunc.h"
#include "printfunc.h"
#include "strfunc.h"


// Print header with optional subtitle
void printHeader(std::string title = "") {
    cpt::printpg();
    cpt::printdiv('-', 53);
    cpt::println("Coordinator");
    cpt::printdiv('-', 53);
    if (!(title == "")) {
        cpt::println(title);
        cpt::printdiv('-', 53);
    }
    cpt::println();
}

int printMenu(std::string title,
              std::string subtitle,
              std::map<int, std::string> choices,
              std::map<int, std::string> params = { },
              bool useAlphabets = false) {
    
    const std::map<int, char> alphabets = {
        {0, 'a'},
        {1, 'b'},
        {2, 'c'},
        {3, 'd'}
    };
    int selectedChoice = 0;
    
    // Print standard elements
    printHeader(title);
    if (!(subtitle == "")) {
        cpt::println(subtitle);
        cpt::println();
    }
    
    // Print menu items
    for (auto& choice: choices) {
        
        std::string menuItemText = choice.second;
        
        for (auto& param: params) {
            if (menuItemText.find("%" + std::to_string(param.first)) != std::string::npos) {
                menuItemText.replace(menuItemText.find("%" + std::to_string(param.first)), 2, param.second);
            }
        }
        
        if (useAlphabets) {
            cpt::print(std::string(1, alphabets.at(choice.first)));
        } else {
            cpt::print(std::to_string(choice.first));
        }
        cpt::print(") ");
        cpt::print(menuItemText);
        cpt::println();
        
    }
    
    do {
    
        cpt::println();
        cpt::print("Please enter your choice: ");;
        std::cin >> selectedChoice;
        std::cin.clear();
        
        if (choices.find(selectedChoice) == choices.end()) {
            cpt::println("Invalid choice, please try again.");
            selectedChoice = 0;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while (selectedChoice == 0);
    
    return selectedChoice;

}

int main() {
    
    // Constant declarations for menu items
    const std::map<int, std::string> mainMenuOptions = {
        {1, "Load data"},
        {2, "Specify filtering criteria (current: %2)"},
        {3, "Specify sorting criteria (current: %3)"},
        {4, "Specify sorting order (current: %4)"},
        {5, "View data"},
        {6, "Store data"},
        {7, "Quit"}
    };
    const std::map<int, std::string> subMenu2Options = {
        {1, "Point2D only"},
        {2, "Point3D only"},
        {3, "Line2D only"},
        {4, "Line3D only"}
    };
    const std::map<int, std::string> subMenu2Prefs = {
        {0, "<not selected>"},
        {1, "Point2D"},
        {2, "Point3D"},
        {3, "Line2D"},
        {4, "Line3D"}
    };
    const std::map<int, std::string> subMenu3OptionsForPoint2D = {
        {1, "X coordinates"},
        {2, "Y coordinates"},
        {7, "Distance from origin"}
    };
    const std::map<int, std::string> subMenu3PrefsForPoint2D = {
        {0, "<not selected>"},
        {1, "X coordinates"},
        {2, "Y coordinates"},
        {7, "distance from origin"}
    };
    const std::map<int, std::string> subMenu3OptionsForPoint3D = {
        {1, "X coordinates"},
        {2, "Y coordinates"},
        {3, "Z coordinates"},
        {7, "Distance from origin"}
    };
    const std::map<int, std::string> subMenu3PrefsForPoint3D = {
        {0, "<not selected>"},
        {1, "X coordinates"},
        {2, "Y coordinates"},
        {3, "Z coordinates"},
        {7, "distance from origin"}
    };
    const std::map<int, std::string> subMenu3OptionsForLines = {
        {4, "Point 1 coordinates"},
        {5, "Point 2 coordinates"},
        {6, "Length"}
    };
    const std::map<int, std::string> subMenu3PrefsForLines = {
        {0, "<not selected>"},
        {4, "point 1"},
        {5, "point 2"},
        {6, "length"}
    };
    const std::map<int, std::string> subMenu4Options = {
        {1, "Ascending"},
        {2, "Descending"},
    };
    const std::map<int, std::string> subMenu4Prefs = {
        {0, "<not selected>"},
        {1, "ascending"},
        {2, "descending"},
    };
    
    // Declarations for system use only
    bool isEnterKeyPressed;
    int currentPref = 0,
        numberOfRecords = 0,
        numberOfDupesRemoved = 0,
        prefFilter = 1,
        prefSorting = 1,
        prefSortOrder = 1;
    std::ifstream fileReader;
    std::ofstream fileWriter;
    std::string dataFilename,
                outFilename,
                strFileReaderLine,
                strOutput;
    std::stringstream sstOutput;
    
    // Declarations for storage of data
    std::vector<Point2D> point2Ds;
    std::vector<Point3D> point3Ds;
    std::vector<Line2D> line2Ds;
    std::vector<Line3D> line3Ds;
    
    do {
        
        std::map<int, std::string> menuParams = {
            {2, subMenu2Prefs.at(prefFilter)},
            {3, ((prefFilter != 0 && prefFilter > 2) ? subMenu3PrefsForLines.at(prefSorting) : subMenu3PrefsForPoint3D.at(prefSorting))},
            {4, subMenu4Prefs.at(prefSortOrder)}
        };
        
        // Pref format: 10x + y, where x is the main menu option and y is the submenu option
        currentPref = 10 * printMenu("",
                                     "Welcome to Coordinator. Choose an option to continue.",
                                     mainMenuOptions,
                                     menuParams);
        
        // Main menu options
        
        switch (currentPref) {
            case 10:
                
                printHeader("Load Data");
                
                // Get the filename of the text file
                cpt::print("Please enter the filename of the text file containing the data: ");
                std::cin >> dataFilename;
                
                // Try to read the file
                try {
                    provideStream(dataFilename, fileReader);
                } catch (std::string e) {
                    cpt::println(e);
                    return 1;
                }
                
                cpt::print("Reading data... ");
                
                // Start reading the data
                while (fileReader.good()) {
                    while (getline(fileReader, strFileReaderLine)) {
                        
                        if (startsWith(strFileReaderLine, "point2d")) {
                            
                            Point2D* pt2 = getPoint2D(strFileReaderLine);
                            
                            // Add the point if it is unique
                            if (std::find_if(point2Ds.begin(), point2Ds.end(), [pt2](Point2D ptInVector) {
                                return ptInVector == *pt2;
                            }) != point2Ds.end()) {
                                delete pt2;
                                ++numberOfDupesRemoved;
                            } else {
                                point2Ds.push_back(*pt2);
                                ++numberOfRecords;
                            }
                            
                        } else if (startsWith(strFileReaderLine, "point3d")) {
                            
                            Point3D* pt3 = getPoint3D(strFileReaderLine);
                            
                            // Add the point if it is unique
                            if (std::find_if(point3Ds.begin(), point3Ds.end(), [pt3](Point3D ptInVector) {
                                return ptInVector == *pt3;
                            }) != point3Ds.end()) {
                                delete pt3;
                                ++numberOfDupesRemoved;
                            } else {
                                point3Ds.push_back(*pt3);
                                ++numberOfRecords;
                            }
                            
                        } else if (startsWith(strFileReaderLine, "line2d")) {
                            
                            Line2D* ln2 = getLine2D(strFileReaderLine);
                            
                            // Add the line if it is unique
                            if (std::find_if(line2Ds.begin(), line2Ds.end(), [ln2](Line2D lnInVector) {
                                return lnInVector == *ln2;
                            }) != line2Ds.end()) {
                                delete ln2;
                                ++numberOfDupesRemoved;
                            } else {
                                line2Ds.push_back(*ln2);
                                ++numberOfRecords;
                            }
                            
                        } else if (startsWith(strFileReaderLine, "line3D")) {
                            
                            Line3D* ln3 = getLine3D(strFileReaderLine);
                            
                            // Add the line if it is unique
                            if (std::find_if(line3Ds.begin(), line3Ds.end(), [ln3](Line3D lnInVector) {
                                return lnInVector == *ln3;
                            }) != line3Ds.end()) {
                                delete ln3;
                                ++numberOfDupesRemoved;
                            } else {
                                line3Ds.push_back(*ln3);
                                ++numberOfRecords;
                            }
                            
                        }
                        
                    }
                }
                
                cpt::println("done.");
                cpt::println();
                
                cpt::print(numberOfRecords);
                cpt::println(" record(s) loaded successfully, of which:");
                cpt::print(point2Ds.size());
                cpt::println(" are Point2D object(s),");
                cpt::print(point3Ds.size());
                cpt::println(" are Point3D object(s),");
                cpt::print(line2Ds.size());
                cpt::println(" are Line2D object(s), and");
                cpt::print(line3Ds.size());
                cpt::println(" are Line3D object(s).");
                cpt::print(numberOfDupesRemoved);
                cpt::println(" duplicate record(s) were not loaded.");
                cpt::println();
                break;
                
            case 20:
                
                currentPref += printMenu("Filter Data", "", subMenu2Options);
                break;
                
            case 30:
                
                switch (prefFilter) {
                    case 0:
                        printHeader("Sort Data");
                        cpt::println("Please select a filtering criteria, then select a sorting criteria.");
                        cpt::println();
                        break;
                    case 1:
                        currentPref += printMenu("Sort Data", "", subMenu3OptionsForPoint2D);
                        break;
                    case 2:
                        currentPref += printMenu("Sort Data", "", subMenu3OptionsForPoint3D);
                        break;
                    case 3:
                    case 4:
                        currentPref += printMenu("Sort Data", "", subMenu3OptionsForLines);
                        break;
                }
                break;
                
            case 40:
                
                currentPref += printMenu("Sort Order", "", subMenu4Options);
                break;
                
            case 50:
                
                printHeader("View Data");
                cpt::println("Filtering criteria: " + subMenu2Options.at(prefFilter));
                cpt::println("Sorting criteria  : " + ((prefFilter != 0 && prefFilter > 2) ? subMenu3OptionsForLines.at(prefSorting) : subMenu3OptionsForPoint3D.at(prefSorting)));
                cpt::println("Sorting order     : " + subMenu4Options.at(prefSortOrder));
                cpt::println();
                
                sstOutput.str(std::string());
                sstOutput.clear();
                
                switch (prefFilter) {
                    case 1: // Point2D
                        
                        switch (prefSorting) {
                            case 1: // X coordinate
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(point2Ds.begin(), point2Ds.end(), [](Point2D a, Point2D b) {
                                            return a.getX() < b.getX();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(point2Ds.begin(), point2Ds.end(), [](Point2D a, Point2D b) {
                                            return a.getX() > b.getX();
                                        });
                                        break;
                                }
                                break;
                            case 2: // Y coordinate
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(point2Ds.begin(), point2Ds.end(), [](Point2D a, Point2D b) {
                                            return a.getY() < b.getY();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(point2Ds.begin(), point2Ds.end(), [](Point2D a, Point2D b) {
                                            return a.getY() > b.getY();
                                        });
                                        break;
                                }
                                break;
                            case 7: // Distance from origin
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(point2Ds.begin(), point2Ds.end(), [](Point2D a, Point2D b) {
                                            return a.getScalarValue() < b.getScalarValue();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(point2Ds.begin(), point2Ds.end(), [](Point2D a, Point2D b) {
                                            return a.getScalarValue() > b.getScalarValue();
                                        });
                                        break;
                                }
                                break;
                        }
                        
                        sstOutput << "    X     Y    Dist. Fr Origin" << std::endl;
                        sstOutput << "- - - - - - - - - - - - - - - - - - -" << std::endl;
                        
                        for (Point2D pt: point2Ds) {
                            sstOutput << "[";
                            sstOutput << std::right << std::setw(4) << pt.getX();
                            sstOutput << ", ";
                            sstOutput << std::right << std::setw(4) << pt.getY();
                            sstOutput << "]" << "   ";
                            sstOutput << std::left << std::fixed << std::setprecision(3) << pt.getScalarValue();
                            sstOutput << std::endl;
                        }
                        
                        cpt::println(sstOutput.str());
                        break;
                        
                    case 2: // Point3D
                        
                        switch (prefSorting) {
                            case 1: // X coordinate
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(point3Ds.begin(), point3Ds.end(), [](Point3D a, Point3D b) {
                                            return a.getX() < b.getX();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(point3Ds.begin(), point3Ds.end(), [](Point3D a, Point3D b) {
                                            return a.getX() > b.getX();
                                        });
                                        break;
                                }
                                break;
                            case 2: // Y coordinate
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(point3Ds.begin(), point3Ds.end(), [](Point3D a, Point3D b) {
                                            return a.getY() < b.getY();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(point3Ds.begin(), point3Ds.end(), [](Point3D a, Point3D b) {
                                            return a.getY() > b.getY();
                                        });
                                        break;
                                }
                                break;
                            case 3: // Z coordinate
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(point3Ds.begin(), point3Ds.end(), [](Point3D a, Point3D b) {
                                            return a.getZ() < b.getZ();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(point3Ds.begin(), point3Ds.end(), [](Point3D a, Point3D b) {
                                            return a.getZ() > b.getZ();
                                        });
                                        break;
                                }
                                break;
                            case 7: // Distance from origin
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(point3Ds.begin(), point3Ds.end(), [](Point3D a, Point3D b) {
                                            return a.getScalarValue() < b.getScalarValue();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(point3Ds.begin(), point3Ds.end(), [](Point3D a, Point3D b) {
                                            return a.getScalarValue() > b.getScalarValue();
                                        });
                                        break;
                                }
                                break;
                        }
                        
                        sstOutput << "    X     Y     Z    Dist. Fr Origin" << std::endl;
                        sstOutput << "- - - - - - - - - - - - - - - - - - -" << std::endl;
                        
                        for (Point3D pt: point3Ds) {
                            sstOutput << "[";
                            sstOutput << std::right << std::setw(4) << pt.getX();
                            sstOutput << ", ";
                            sstOutput << std::right << std::setw(4) << pt.getY();
                            sstOutput << ", ";
                            sstOutput << std::right << std::setw(4) << pt.getZ();
                            sstOutput << "]" << "   ";
                            sstOutput << std::left << std::fixed << std::setprecision(3) << pt.getScalarValue();
                            sstOutput << std::endl;
                        }
                        
                        cpt::println(sstOutput.str());
                        break;
                        
                    case 3: // Line2D
                        
                        switch (prefSorting) {
                            case 4: // Point 1 coordinate
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(line2Ds.begin(), line2Ds.end(), [](Line2D a, Line2D b) {
                                            return a.getPt1().getScalarValue() < b.getPt1().getScalarValue();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(line2Ds.begin(), line2Ds.end(), [](Line2D a, Line2D b) {
                                            return a.getPt1().getScalarValue() > b.getPt1().getScalarValue();
                                        });
                                        break;
                                }
                                break;
                            case 5: // Point 2 coordinate
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(line2Ds.begin(), line2Ds.end(), [](Line2D a, Line2D b) {
                                            return a.getPt2().getScalarValue() < b.getPt2().getScalarValue();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(line2Ds.begin(), line2Ds.end(), [](Line2D a, Line2D b) {
                                            return a.getPt2().getScalarValue() > b.getPt2().getScalarValue();
                                        });
                                        break;
                                }
                                break;
                            case 6: // Length
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(line2Ds.begin(), line2Ds.end(), [](Line2D a, Line2D b) {
                                            return a.getScalarValue() < b.getScalarValue();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(line2Ds.begin(), line2Ds.end(), [](Line2D a, Line2D b) {
                                            return a.getScalarValue() > b.getScalarValue();
                                        });
                                        break;
                                }
                                break;
                        }
                        
                        sstOutput << " P1-X  P1-Y     P2-X  P2-Y    Length" << std::endl;
                        sstOutput << "- - - - - - - - - - - - - - - - - - -" << std::endl;
                        
                        for (Line2D ln: line2Ds) {
                            sstOutput << "[";
                            sstOutput << std::right << std::setw(4) << ln.getPt1().getX();
                            sstOutput << ", ";
                            sstOutput << std::right << std::setw(4) << ln.getPt1().getY();
                            sstOutput << "]" << "   " << "[";
                            sstOutput << std::right << std::setw(4) << ln.getPt2().getX();
                            sstOutput << ", ";
                            sstOutput << std::right << std::setw(4) << ln.getPt2().getY();
                            sstOutput << "]" << "   ";
                            sstOutput << std::left << std::fixed << std::setprecision(3) << ln.getScalarValue();
                            sstOutput << std::endl;
                        }
                        
                        cpt::println(sstOutput.str());
                        break;
                        
                    case 4: // Line3D
                        
                        switch (prefSorting) {
                            case 4: // Point 1 coordinate
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(line3Ds.begin(), line3Ds.end(), [](Line3D a, Line3D b) {
                                            return a.getPt1().getScalarValue() < b.getPt1().getScalarValue();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(line3Ds.begin(), line3Ds.end(), [](Line3D a, Line3D b) {
                                            return a.getPt1().getScalarValue() > b.getPt1().getScalarValue();
                                        });
                                        break;
                                }
                                break;
                            case 5: // Point 2 coordinate
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(line3Ds.begin(), line3Ds.end(), [](Line3D a, Line3D b) {
                                            return a.getPt2().getScalarValue() < b.getPt2().getScalarValue();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(line3Ds.begin(), line3Ds.end(), [](Line3D a, Line3D b) {
                                            return a.getPt2().getScalarValue() > b.getPt2().getScalarValue();
                                        });
                                        break;
                                }
                                break;
                            case 6: // Length
                                switch (prefSortOrder) {
                                    case 1: // Ascending
                                        std::sort(line3Ds.begin(), line3Ds.end(), [](Line3D a, Line3D b) {
                                            return a.getScalarValue() < b.getScalarValue();
                                        });
                                        break;
                                    case 2: // Descending
                                        std::sort(line3Ds.begin(), line3Ds.end(), [](Line3D a, Line3D b) {
                                            return a.getScalarValue() > b.getScalarValue();
                                        });
                                        break;
                                }
                                break;
                        }
                        
                        sstOutput << " P1-X  P1-Y  P1-Z     P1-X  P1-Y  P1-Z    Length" << std::endl;
                        sstOutput << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
                        
                        for (Line3D ln: line3Ds) {
                            sstOutput << "[";
                            sstOutput << std::right << std::setw(4) << ln.getPt1().getX();
                            sstOutput << ", ";
                            sstOutput << std::right << std::setw(4) << ln.getPt1().getY();
                            sstOutput << ", ";
                            sstOutput << std::right << std::setw(4) << ln.getPt1().getZ();
                            sstOutput << "]" << "   " << "[";
                            sstOutput << std::right << std::setw(4) << ln.getPt2().getX();
                            sstOutput << ", ";
                            sstOutput << std::right << std::setw(4) << ln.getPt2().getY();
                            sstOutput << ", ";
                            sstOutput << std::right << std::setw(4) << ln.getPt2().getZ();
                            sstOutput << "]" << "   ";
                            sstOutput << std::left << std::fixed << std::setprecision(3) << ln.getScalarValue();
                            sstOutput << std::endl;
                        }
                        
                        cpt::println(sstOutput.str());
                        break;
                        
                }
                
                break;
                
            case 60:
                
                printHeader("Save Data");
                
                // Get the filename of the file to save to
                cpt::print("Please enter the filename of the text file to save the previous output to: ");
                std::cin >> outFilename;
                fileWriter.open(outFilename);
                cpt::print("Saving file...");
                fileWriter << sstOutput.rdbuf();
                cpt::println("done.");
                cpt::println();
                break;
                
        }
        
        // Sub-menu options
        
        switch (currentPref) {
            case 21:
                prefFilter = 1;
                prefSorting = 1;
                cpt::println("Filtering criteria successfully set to Point2D.");
                cpt::println();
                break;
            case 22:
                prefFilter = 2;
                prefSorting = 1;
                cpt::println("Filtering criteria successfully set to Point3D.");
                cpt::println();
                break;
            case 23:
                prefFilter = 3;
                prefSorting = 4;
                cpt::println("Filtering criteria successfully set to Line2D.");
                cpt::println();
                break;
            case 24:
                prefFilter = 4;
                prefSorting = 4;
                cpt::println("Filtering criteria successfully set to Line3D.");
                cpt::println();
                break;
            case 31:
                prefSorting = 1;
                cpt::println("Sorting criteria successfully set to X coordinates.");
                cpt::println();
                break;
            case 32:
                prefSorting = 2;
                cpt::println("Sorting criteria successfully set to Y coordinates.");
                cpt::println();
                break;
            case 33:
                prefSorting = 3;
                cpt::println("Sorting criteria successfully set to Z coordinates.");
                cpt::println();
                break;
            case 34:
                prefSorting = 4;
                cpt::println("Sorting criteria successfully set to point 1 coordinates.");
                cpt::println();
                break;
            case 35:
                prefSorting = 5;
                cpt::println("Sorting criteria successfully set to point 2 coordinates.");
                cpt::println();
                break;
            case 36:
                prefSorting = 6;
                cpt::println("Sorting criteria successfully set to length.");
                cpt::println();
                break;
            case 37:
                prefSorting = 7;
                cpt::println("Sorting criteria successfully set to distance from origin.");
                cpt::println();
                break;
            case 41:
                prefSortOrder = 1;
                cpt::println("Sorting order successfully set to ascending.");
                cpt::println();
                break;
            case 42:
                prefSortOrder = 2;
                cpt::println("Sorting order successfully set to descending.");
                cpt::println();
                break;
        }
        
        if (currentPref != 70) {
            cpt::print("Press Enter to return to the main menu.");
            if (currentPref == 10 || currentPref == 60) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.clear();
            }
            isEnterKeyPressed = false;
            while (!isEnterKeyPressed) {
                if (std::cin.get() == '\n') {
                    isEnterKeyPressed = true;
                }
            }
        }
        
    } while (currentPref != 70);
    
    printHeader();
    cpt::println("Thank you for using Coordinator.");
    cpt::println();
    
    return 0;
}

// Finally resolved the sorting issues which were also in A2
// Thanks to Dreamy#8029 and zero9178#6333 for assisting

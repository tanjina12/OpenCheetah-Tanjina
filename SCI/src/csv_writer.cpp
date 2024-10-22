/** CSV_WRITER.cpp
 * 
 * Created by Tanjina
 * Creation date:
 * 15 Oct 2024
 * Last Edit on:
 * 21 Oct 2024
 * 
 * Description:
 * Main file for the CSV Writer library
 **/
#include "csv_writer.hpp"
#include <iostream>
#include <vector>
#include <variant> // For multiple data types

/***** IMPLEMENTATIONS *****/
WriteToCSV::WriteToCSV(const std::string &output_file_name, const std::vector<std::string>& headers)
{
    csvFile.open(output_file_name, std::ios::out); // Open the file

    if(csvFile.is_open()){
        // Write the CSV headers
        if(!headers.empty()){
            for(size_t i = 0; i < headers.size(); i++){
                csvFile << headers[i];
                if(i < headers.size() - 1){
                    csvFile << ","; // Added comma between each cloumn but the last column
                }
            }
            csvFile << "\n";
        }
        //csvFile << "i,layer_name,layer_counter,timestamp_power_reading,avg_power_usage\n";
    }else{
        std::cerr << "ERROR: Failed to open the CSV file: " << output_file_name << std::endl;
        return;
    }
}

/* Method to write a data row into the output CSV file (for fixed columns) */
void WriteToCSV::insertDataRow(int i, const std::string &layer_name, int layer_counter, int64_t timestamp_power_reading, double avg_power_usage)
{
    if(csvFile.is_open()){
        // Write the data row to the output CSV file
        csvFile << i << "," << layer_name << "," << layer_counter << "," << timestamp_power_reading << "," << avg_power_usage <<"\n";
    }else{
        std::cerr << "ERROR: CSV file is not open for writing" << std::endl;
        return;
    }
}

// /* Method to define custom headers to the CSV file*/
// void WriteToCSV::writeCSVHeaders(const std::vector<std::string>& headers){
//     if(csvFile.is_open()){
//         for(size_t i = 0; i < headers.size(); i++){
//             csvFile << headers[i];
//             if(i < headers.size() - 1){
//                 csvFile << ","; // Added comma between each cloumn but the last column
//             }
//         }
//         csvFile << "\n";
//     }else{
//         std::cerr << "ERROR: CSV file is not open for writing" << std::endl;
//         return;
//     }

// }
/* Method to handle data row with mixed column types using csv_column_type variant */ 
void WriteToCSV::insertDataRow(const std::vector<csv_column_type>& dataRow_values){
    if(csvFile.is_open()){
        for(size_t i = 0; i < dataRow_values.size(); i++){
            //csvFile << dataRow_values[i];
            std::visit([&](auto&& arg) { csvFile << arg; }, dataRow_values[i]);
            if(i < dataRow_values.size() - 1){
                csvFile << ","; // Added comma between each cloumn but the last column
            }
        }
        csvFile << "\n";
    }else{
        std::cerr << "ERROR: CSV file is not open for writing" << std::endl;
        return;
    }   
}
// /* Method to write a data row into the output CSV file (for flexible columns) */
// void WriteToCSV::insertDataRow(const std::vector<std::string>& dataRow_values){
//     if(csvFile.is_open()){
//         for(size_t i = 0; i < dataRow_values.size(); i++){
//             csvFile << dataRow_values[i];
//             if(i < dataRow_values.size() - 1){
//                 csvFile << ","; // Added comma between each cloumn but the last column
//             }
//         }
//         csvFile << "\n";
//     }else{
//         std::cerr << "ERROR: CSV file is not open for writing" << std::endl;
//         return;
//     }

// }
/* Method to write a data row into the output CSV file (for flexible columns) with int64_t data type values */
// void WriteToCSV::insertDataRow(const std::vector<int64_t>& dataRow_values){
//     if(csvFile.is_open()){
//         for(size_t i = 0; i < dataRow_values.size(); i++){
//             csvFile << dataRow_values[i];
//             if(i < dataRow_values.size() - 1){
//                 csvFile << ","; // Added comma between each cloumn but the last column
//             }
//         }
//         csvFile << "\n";
//     }else{
//         std::cerr << "ERROR: CSV file is not open for writing" << std::endl;
//         return;
//     }

// }
// /* Method to write a data row into the output CSV file (for flexible columns) with int32_t data type values */
// void WriteToCSV::insertDataRow(const std::vector<int32_t>& dataRow_values){
//     if(csvFile.is_open()){
//         for(size_t i = 0; i < dataRow_values.size(); i++){
//             csvFile << dataRow_values[i];
//             if(i < dataRow_values.size() - 1){
//                 csvFile << ","; // Added comma between each cloumn but the last column
//             }
//         }
//         csvFile << "\n";
//     }else{
//         std::cerr << "ERROR: CSV file is not open for writing" << std::endl;
//         return;
//     }

// }
/* Destructor */
WriteToCSV::~WriteToCSV()
{
    if(csvFile.is_open()){
        csvFile.close(); // Close the output CSV file
    }
}
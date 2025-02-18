#include <gtest/gtest.h>
#include "CDSVReader.h"  // Not CDSVReader.cpp
#include "StringDataSource.h" // Not StringDataSource.cpp
#include <memory>
#include <vector>
#include <string>

TEST(DSVReaderTest, ReadsSimpleRow) {
    std::shared_ptr<CDataSource> source = std::make_shared<CStringDataSource>("a,b,c\n1,2,3\n");
    CDSVReader reader(source, ',');
    std::vector<std::string> row;
    
    EXPECT_TRUE(reader.ReadRow(row));
    EXPECT_EQ(row.size(), 3);
    EXPECT_EQ(row[0], "a");
    EXPECT_EQ(row[1], "b");
    EXPECT_EQ(row[2], "c");
}
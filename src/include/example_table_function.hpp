#pragma once

#include <duckdb.hpp>

namespace duckdb {

struct ExampleTableData : public TableFunctionData {
	bool data_returned = false; // Add this flag
	int value = 0;              // for passed in matrix start value
	vector<Value> col1;
	vector<Value> col2;
	vector<Value> col3;
	vector<Value> col4;
	vector<Value> col5;

	ExampleTableData() {
	}
};

unique_ptr<FunctionData> ExampleTableBindFunction(ClientContext &context, TableFunctionBindInput &input,
                                                  vector<LogicalType> &return_types, vector<string> &names);

void ExampleTableFunction(ClientContext &context, TableFunctionInput &data_p, DataChunk &output);

} // namespace duckdb

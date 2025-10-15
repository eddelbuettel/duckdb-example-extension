#define DUCKDB_EXTENSION_MAIN

#include "example_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/function/scalar_function.hpp"
#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>

// OpenSSL linked through vcpkg
#include <openssl/opensslv.h>

namespace duckdb {

inline void ExampleScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &name_vector = args.data[0];
	UnaryExecutor::Execute<string_t, string_t>(name_vector, result, args.size(), [&](string_t name) {
		return StringVector::AddString(result, "Example " + name.GetString() + " 🐥");
	});
}

inline void ExampleOpenSSLVersionScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &name_vector = args.data[0];
	UnaryExecutor::Execute<string_t, string_t>(name_vector, result, args.size(), [&](string_t name) {
		return StringVector::AddString(result, "Example " + name.GetString() + ", my linked OpenSSL version is " +
		                                           OPENSSL_VERSION_TEXT);
	});
}

static void LoadInternal(ExtensionLoader &loader) {
	// Register a scalar function
	auto example_scalar_function = ScalarFunction("example", {LogicalType::VARCHAR}, LogicalType::VARCHAR, ExampleScalarFun);
	loader.RegisterFunction(example_scalar_function);

	// Register another scalar function
	auto example_openssl_version_scalar_function = ScalarFunction("example_openssl_version", {LogicalType::VARCHAR},
	                                                            LogicalType::VARCHAR, ExampleOpenSSLVersionScalarFun);
	loader.RegisterFunction(example_openssl_version_scalar_function);
}

void ExampleExtension::Load(ExtensionLoader &loader) {
	LoadInternal(loader);
}
std::string ExampleExtension::Name() {
	return "example";
}

std::string ExampleExtension::Version() const {
#ifdef EXT_VERSION_EXAMPLE
	return EXT_VERSION_EXAMPLE;
#else
	return "";
#endif
}

} // namespace duckdb

extern "C" {

DUCKDB_CPP_EXTENSION_ENTRY(example, loader) {
	duckdb::LoadInternal(loader);
}
}

#include "ERP.hpp"

const string INPUT_FILE_NAME = "input.txt";
const string OUTPUT_FILE_NAME = "output.txt";

int main() {
	ERP erp(INPUT_FILE_NAME, OUTPUT_FILE_NAME);
	erp.run();
	return EXIT_SUCCESS;
}
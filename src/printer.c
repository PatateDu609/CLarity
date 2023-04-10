#include "printer.h"
#include <stdio.h>
#include <string.h>

#define CL_TEST_SEPARATOR_CHAR '='
#define CL_SUITE_SEPARATOR_CHAR '*'
#define CL_TEST_SEPARATOR_LENGTH ((uint32_t)80)
#define CL_SUITE_SEPARATOR_LENGTH ((uint32_t)100)
#define CL_TEST_INDENTATION_STR "\t"

#define CL_SUITE_REPORT_LENGTH ((uint32_t)120)


static const char *__cl_stringify_boolean(bool b, const char *true_str, const char *false_str) {
	return b ? true_str : false_str;
}


static void __cl_print_line_separator(char c, uint32_t l) {
	for (uint32_t i = 0; i < l; i++)
		printf("%c", c);
	printf("\n");
}


/**
 * @brief Writes the given text in a box with the given border character
 *
 * The box will be sized to fit the provided text, and the text will be perfectly centered
 * within the box. If the text cannot be perfectly centered (due to an even number of characters
 * in the box), the extra character will be added to the left side of the box.
 *
 * @param text The text to write in the box
 * @param border_char The character to use for the box borders
 * @param box_width The width of the box
 * @param enable_top Enables or disables the top border
 *
 * @note However no further treatment is done, to disallow words to be split by the box.
 */
static void __cl_write_box(const char *text, char border, size_t width, bool enable_top) {
	// Calculate the height of the box
	size_t len = strlen(text);
	size_t height = 1;
	size_t remaining_space = width - 2;
	while (len > remaining_space) {
		len -= remaining_space;
		height++;
	}

	if (enable_top)
	// Print top border
		__cl_print_line_separator(border, width);

	// Print sides and text
	size_t start = 0;
	for (size_t i = 0; i < height; i++) {
		size_t end = start + remaining_space;
		if (end > strlen(text)) {
			end = strlen(text);
		}

		// Print left border
		printf("%c", border);

		// Print spaces or text
		size_t spaces = remaining_space - (end - start);
		size_t left_spaces = spaces / 2;
		size_t right_spaces = spaces - left_spaces;
		for (size_t j = 0; j < left_spaces; j++)
			printf(" ");
		for (size_t j = start; j < end; j++)
			printf("%c", text[j]);
		for (size_t j = 0; j < right_spaces; j++)
			printf(" ");

		// Print right border
		printf("%c\n", border);

		start = end;
	}

	// Print bottom border
	__cl_print_line_separator(border, width);
}


void cl_print_test_result(clarity_test_result_t *result) {
	if (!result->skipped && !result->passed)
		__cl_print_line_separator(CL_TEST_SEPARATOR_CHAR, CL_TEST_SEPARATOR_LENGTH);

	printf("[%s] Result: ", result->name);
	if (result->skipped) {
		printf("SKIPPED\n");
		return;
	}

	printf("%s\n", __cl_stringify_boolean(result->passed, "PASS", "FAIL"));
	if (result->passed)
		return;

	printf("%s%s\n", CL_TEST_INDENTATION_STR, result->error_message);
	printf("%sFile: %s:%d\n", CL_TEST_INDENTATION_STR, result->file_name, result->line_number);
}


void cl_print_suite_name(const char *name) {
	__cl_write_box(name, CL_SUITE_SEPARATOR_CHAR, CL_SUITE_SEPARATOR_LENGTH, true);
}

void cl_print_suite_report(clarity_suite_report_t *report) {
	__cl_write_box(report->name, CL_SUITE_SEPARATOR_CHAR, CL_SUITE_REPORT_LENGTH, true);

	int spacing = 5;

	char text[CL_SUITE_REPORT_LENGTH];
	snprintf(text, sizeof CL_SUITE_REPORT_LENGTH,
			 "Total: %-*d Succeeded: %-*d Failed: %-*d Skipped: %-*d",
			 spacing, report->total_tests,
			 spacing, report->succeeded_tests,
			 spacing, report->failed_tests,
			 spacing, report->skipped_tests);

	__cl_write_box(text, CL_SUITE_SEPARATOR_CHAR, CL_SUITE_REPORT_LENGTH, false);
}
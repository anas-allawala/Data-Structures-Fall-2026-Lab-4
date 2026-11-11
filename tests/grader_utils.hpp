#ifndef GRADER_UTILS_HPP
#define GRADER_UTILS_HPP

#include "../include/doctest.h"
#include <string>
#include <vector>

struct CaseState {
    std::string task;
    std::string case_id;
    int attempts_seen = 0;
    int pass_count = 0;
    int fail_count = 0;
    std::string last_result = "NONE";
};

struct LabLoggerReporter : public doctest::IReporter {
    const doctest::ContextOptions& opt;
    int total_passed = 0;
    int total_failed = 0;
    int total_awarded_marks = 0;
    int total_possible_marks = 0; 

    LabLoggerReporter(const doctest::ContextOptions& in);

    void test_case_end(const doctest::CurrentTestCaseStats& st) override;
    void test_run_end(const doctest::TestRunStats& st) override;

    void report_query(const doctest::QueryData&) override {}
    void test_run_start() override {}
    void test_case_start(const doctest::TestCaseData&) override {}
    void test_case_reenter(const doctest::TestCaseData&) override {}
    void test_case_exception(const doctest::TestCaseException&) override {}
    void subcase_start(const doctest::SubcaseSignature&) override {}
    void subcase_end() override {}
    void log_assert(const doctest::AssertData&) override {}
    void log_message(const doctest::MessageData&) override {}
    void test_case_skipped(const doctest::TestCaseData&) override {}
};

#endif
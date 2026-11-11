#include "grader_utils.hpp"
#include <sys/stat.h>
#include <ctime>
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <direct.h>
#define make_dir(path) _mkdir(path)
#else
#define make_dir(path) mkdir(path, 0777)
#endif

using namespace std;

static vector<CaseState> g_states;
static bool g_state_loaded = false;

static string current_time_str() {
  time_t now = time(nullptr);
  tm* t = localtime(&now);
  char buffer[64];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", t);
  return string(buffer);
}

static vector<string> split_tsv(const string& line) {
  vector<string> parts;
  string current;
  for (char ch : line) {
    if (ch == '\t') {
      parts.push_back(current);
      current.clear();
    } else if (ch != '\r' && ch != '\n') {
      current.push_back(ch);
    }
  }
  parts.push_back(current);
  return parts;
}

static string case_description(const string& case_id) {
  // ==========================================
  // TASK 1: Adjacency Matrix (25 Marks)
  // ==========================================
  if (case_id == "t1_add_edge")
    return "Adjacency Matrix: add_edge correctly updates the 2D array";
  else if (case_id == "t1_remove_edge")
    return "Adjacency Matrix: remove_edge clears array elements";
  else if (case_id == "t1_has_edge")
    return "Adjacency Matrix: has_edge correctly reads the array";
  else if (case_id == "t1_degree")
    return "Adjacency Matrix: degree counts connections accurately";

  // ==========================================
  // TASK 2: Adjacency List (25 Marks)
  // ==========================================
  else if (case_id == "t2_add_edge")
    return "Adjacency List: add_edge pushes to the mapped vector";
  else if (case_id == "t2_remove_edge")
    return "Adjacency List: remove_edge erases from the vector";
  else if (case_id == "t2_has_edge")
    return "Adjacency List: has_edge correctly reads the map";
  else if (case_id == "t2_solve_equation")
    return "Adjacency List: solve_equation parses tree correctly";

  // ==========================================
  // TASK 3: Tries (50 Marks)
  // ==========================================
  else if (case_id == "t3_insert_word")
    return "Trie: insertWord builds nodes and sets end flag correctly";
  else if (case_id == "t3_search_word")
    return "Trie: searchWord correctly parses existing trie nodes";
  else if (case_id == "t3_starts_with")
    return "Trie: startsWith returns all valid prefix matches";

  // Fallback
  return case_id;
}

static void ensure_header(const string& path, const string& header) {
  ifstream check(path);
  if (!check.good()) {
    ofstream f(path);
    if (f) f << header << "\n";
  }
}

static void load_state() {
  if (g_state_loaded) return;
  g_state_loaded = true;
  ifstream f("logs/case_state.tsv");
  if (!f) return;
  string line;
  getline(f, line);
  while (getline(f, line)) {
    vector<string> parts = split_tsv(line);
    if (parts.size() < 6) continue;
    g_states.push_back(
        {parts[0], parts[1], stoi(parts[2]), stoi(parts[3]), stoi(parts[4]), parts[5]});
  }
}

static void save_state() {
  ofstream f("logs/case_state.tsv");
  if (!f) return;
  f << "task\tcase_id\tattempts_seen\tpass_count\tfail_count\tlast_result\n";
  for (const auto& s : g_states) {
    f << s.task << "\t" << s.case_id << "\t" << s.attempts_seen << "\t" << s.pass_count << "\t"
      << s.fail_count << "\t" << s.last_result << "\n";
  }
}

static CaseState* get_or_create_state(const string& task, const string& case_id) {
  load_state();
  for (auto& s : g_states) {
    if (s.task == task && s.case_id == case_id) return &s;
  }
  g_states.push_back(CaseState{task, case_id, 0, 0, 0, "NONE"});
  return &g_states.back();
}

LabLoggerReporter::LabLoggerReporter(const doctest::ContextOptions& in) : opt(in) {
  make_dir("logs");
  make_dir("output");

  ensure_header("logs/test_results.tsv",
                "task\ttask_attempt\tcase_id\tresult\tmarks_awarded\tmarks_total\tfirst_time_"
                "passed_this_attempt\tever_passed_before_this_attempt\tprevious_result");
  ensure_header("logs/task_runs.tsv",
                "task\ttask_attempt\tstart_time\ttotal_marks\ttotal_possible\tpassed_cases\tfailed_"
                "cases\tall_cases_passed");
}

void LabLoggerReporter::test_case_end(const doctest::CurrentTestCaseStats& st) {
  string case_id = (opt.currentTest && opt.currentTest->m_name) ? opt.currentTest->m_name : "unknown_case";
  string task_name = (opt.currentTest && opt.currentTest->m_test_suite) ? opt.currentTest->m_test_suite : "default_task";

  static bool output_cleared = false;
  string output_file = "output/" + task_name + ".txt";

  if (!output_cleared) {
    ofstream out(output_file);
    out.close();
    output_cleared = true;
  }

  bool passed = st.testCaseSuccess;
  if (passed) total_passed++;
  else total_failed++;

  string tsv_result = passed ? "SECURED" : "BUSTED";
  string console_result = passed ? "\033[32m SECURED \033[0m" : "\033[31m BUSTED  \033[0m";

  int marks = 0;

  // ==========================================
  // TASK 1: Adjacency Matrix (25 MARKS)
  // ==========================================
  if (case_id == "t1_add_edge") marks = 5;
  else if (case_id == "t1_remove_edge") marks = 5;
  else if (case_id == "t1_has_edge") marks = 5;
  else if (case_id == "t1_degree") marks = 10;

  // ==========================================
  // TASK 2: Adjacency List (25 MARKS)
  // ==========================================
  else if (case_id == "t2_add_edge") marks = 5;
  else if (case_id == "t2_remove_edge") marks = 5;
  else if (case_id == "t2_has_edge") marks = 5;
  else if (case_id == "t2_solve_equation") marks = 10;

  // ==========================================
  // TASK 3: Tries (50 MARKS)
  // ==========================================
  else if (case_id == "t3_insert_word") marks = 15;
  else if (case_id == "t3_search_word") marks = 15;
  else if (case_id == "t3_starts_with") marks = 20;

  int awarded = passed ? marks : 0;
  total_awarded_marks += awarded;
  total_possible_marks += marks;

  string description = case_description(case_id);
  cout << "[" << console_result << "] " << description << " (" << awarded << "/" << marks << ")\n";

  ofstream out(output_file, ios::app);
  if (out) out << awarded << "/" << marks << "\n";

  CaseState* s = get_or_create_state(task_name, case_id);
  string previous = s->last_result;
  int ever_passed = (s->pass_count > 0) ? 1 : 0;
  int first_time = (passed && s->pass_count == 0) ? 1 : 0;

  s->attempts_seen++;
  if (passed) s->pass_count++;
  else s->fail_count++;
  s->last_result = tsv_result;

  ofstream tr("logs/test_results.tsv", ios::app);
  if (tr) {
    tr << task_name << "\t1\t" << case_id << "\t" << tsv_result << "\t" << awarded << "\t" << marks
       << "\t" << first_time << "\t" << ever_passed << "\t" << previous << "\n";
  }
}

void LabLoggerReporter::test_run_end(const doctest::TestRunStats& st) {
  save_state();
  string task_name = st.numTestCases > 0 && opt.currentTest ? opt.currentTest->m_test_suite : "lab_summary";

  cout << "---------------------------------------\n";
  cout << "Task score: " << total_awarded_marks << "/" << total_possible_marks << "\n";
  cout << "---------------------------------------\n";

  ofstream runs("logs/task_runs.tsv", ios::app);
  if (runs) {
    runs << task_name << "\t1\t" << current_time_str() << "\t" << total_awarded_marks << "\t"
         << total_possible_marks << "\t" << total_passed << "\t" << total_failed << "\t"
         << (total_failed == 0 ? 1 : 0) << "\n";
  }
}

REGISTER_LISTENER("LabLoggerReporter", 1, LabLoggerReporter);
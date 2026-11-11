#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#define make_dir(path) _mkdir(path)
#else
#define make_dir(path) mkdir(path, 0777)
#endif

using namespace std;

static string nowTime() {
  time_t now = time(nullptr);
  char buffer[64];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
  return string(buffer);
}

static string nowTimeFilename() {
  time_t now = time(nullptr);
  char buffer[64];
  strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localtime(&now));
  return string(buffer);
}

static void removeExe(const string& exe) {
  remove(exe.c_str());
  remove((exe + ".exe").c_str());
}

static int runCommand(const string& cmd) { return system(cmd.c_str()); }

static int runTask(const string& task) {
  make_dir("logs");
  make_dir("output");
  string exe = "run_" + task;
  removeExe(exe);

  string compile;

  // LAB 4 ISOLATED COMPILATION TARGETS
  if (task == "task1") {
    // Task 1: Adjacency Matrix
    compile =
        "g++ -std=c++17 -w "
        "code/Graph.cpp "
        "tests/grader_utils.cpp "
        "tests/test_task1.cpp "
        "-Iinclude -Itests -o " + exe;
  } else if (task == "task2") {
    // Task 2: Adjacency List
    compile =
        "g++ -std=c++17 -w "
        "code/Graph.cpp "
        "tests/grader_utils.cpp "
        "tests/test_task2.cpp "
        "-Iinclude -Itests -o " + exe;
  } else if (task == "task3") {
    // Task 3: Tries
    compile =
        "g++ -std=c++17 -w "
        "code/TrieGraph.cpp "
        "tests/grader_utils.cpp "
        "tests/test_task3.cpp "
        "-Iinclude -Itests -o " + exe;
  } else {
    cout << "Unknown task: " << task << endl;
    return 1;
  }

  string temp_log = "logs/temp_compile_" + task + ".txt";
  string compile_cmd = compile + " > " + temp_log + " 2>&1";

  ofstream clog("logs/compile_attempts.tsv", ios::app);
  if (clog) {
    clog << nowTime() << "\t" << task << "\t" << compile << "\n";
    clog.close();
  }

  cout << "Compiling " << task << "..." << endl;
  int c = runCommand(compile_cmd);

  ifstream log_file(temp_log);
  if (log_file) {
    cout << log_file.rdbuf();
    log_file.close();
  }

  if (c != 0) {
    removeExe(exe);
    string err_filename = "logs/compile_error_" + task + "_" + nowTimeFilename() + ".txt";
    ifstream src(temp_log, ios::binary);
    ofstream dst(err_filename, ios::binary);
    if (src && dst) dst << src.rdbuf();
    src.close();
    dst.close();
    remove(temp_log.c_str()); 

    cout << "\033[31mCompilation failed for " << task << ". Stale code cannot run.\033[0m" << endl;
    return 1;
  } else {
    remove(temp_log.c_str());
  }

#ifdef _WIN32
  string run = exe + ".exe";
#else
  string run = "./" + exe;
#endif

  cout << "Running " << task << "..." << endl;
  return runCommand(run);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Usage: ./test_runner task1 | task2 | task3 | all" << endl;
    return 1;
  }

  string task = argv[1];

  if (task == "all") {
    vector<string> tasks = {"task1", "task2", "task3"};
    int failed = 0;
    for (const string& t : tasks) {
      cout << "\n=======================================" << endl;
      cout << "             " << t << "             " << endl;
      cout << "=======================================" << endl;
      if (runTask(t) != 0) failed++;
    }
    return failed == 0 ? 0 : 1;
  }

  return runTask(task);
}
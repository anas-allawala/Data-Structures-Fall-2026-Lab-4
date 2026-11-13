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

// Helper to get time for compilation log
static string nowTime() {
  time_t now = time(nullptr);
  char buffer[64];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
  return string(buffer);
}

// Helper to get a filesystem-safe time string for the error log file
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
  string failed_file_msg;

  // Compile the correct source files based on the Lab 4 structure
  if (task == "task1") {
    compile =
        "g++ -std=c++17 "
        "code/Graph.cpp "
        "tests/grader_utils.cpp "
        "tests/test_task1.cpp "
        "-Iinclude -Itests "
        "-o " +
        exe;
    failed_file_msg = "test_task1.cpp (or Graph.cpp)";
  } else if (task == "task2") {
    compile =
        "g++ -std=c++17 "
        "code/Graph.cpp "
        "tests/grader_utils.cpp "
        "tests/test_task2.cpp "
        "-Iinclude -Itests "
        "-o " +
        exe;
    failed_file_msg = "test_task2.cpp (or Graph.cpp)";
  } else if (task == "task3") {
    compile =
        "g++ -std=c++17 "
        "code/TrieGraph.cpp "
        "tests/grader_utils.cpp "
        "tests/test_task3.cpp "
        "-Iinclude -Itests "
        "-o " +
        exe;
    failed_file_msg = "test_task3.cpp (or TrieGraph.cpp)";
  } else {
    cout << "Unknown task: " << task << endl;
    return 1;
  }

  // Redirect stdout and stderr to a temporary file
  string temp_log = "logs/temp_compile_" + task + ".txt";
  string compile_cmd = compile + " > " + temp_log + " 2>&1";

  // ---> LOG THIS COMPILATION ATTEMPT <---
  ofstream clog("logs/compile_attempts.tsv", ios::app);
  if (clog) {
    clog << nowTime() << "\t" << task << "\t" << compile << "\n";
    clog.close();
  }

  cout << "Compiling " << task << "..." << endl;
  int c = runCommand(compile_cmd);

  // Read and print the captured output to the terminal so the student sees it normally
  ifstream log_file(temp_log);
  if (log_file) {
    cout << log_file.rdbuf();
    log_file.close();
  }

  if (c != 0) {
    removeExe(exe);
    
    string err_filename = "logs/compile_error_" + task + "_" + nowTimeFilename() + ".txt";
    
    // Copy the file contents safely instead of relying on OS-dependent rename()
    ifstream src(temp_log, ios::binary);
    ofstream dst(err_filename, ios::binary);
    
    if (dst) {
        dst << "Failed File: " << failed_file_msg << "\n"; // Inject the failed file line at the top
    }
    if (src && dst) {
        dst << src.rdbuf();
    }
    src.close();
    dst.close();

    remove(temp_log.c_str()); // Clean up temp file

    cout << "Compilation failed for " << task << ". Stale code cannot run." << endl;
    return 1;
  } else {
    // If compilation succeeds, just clean up the temporary log
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
      cout << "\n========== " << t << " ==========" << endl;
      if (runTask(t) != 0) failed++;
    }
    return failed == 0 ? 0 : 1;
  }

  return runTask(task);
}

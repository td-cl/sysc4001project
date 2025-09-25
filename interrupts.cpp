/**
 *
 * @file interrupts.cpp
 * @author Trac-Duy Chu-Le 101220669, Zachary Dredge 101197514
 *
 */

#include <interrupts.hpp>
#include <random>

int main(int argc, char **argv)
{

  // vectors is a C++ std::vector of strings that contain the address of the ISR
  // delays  is a C++ std::vector of ints that contain the delays of each device
  // the index of these elements is the device number, starting from 0
  auto [vectors, delays] = parse_args(argc, argv);
  std::ifstream input_file(argv[1]);

  std::string trace;     //!< string to store single line of trace file
  std::string execution; //!< string to accumulate the execution output

  /******************ADD YOUR VARIABLES HERE*************************/
  int timer = 0;

  /******************************************************************/

  // parse each line of the input trace file
  while (std::getline(input_file, trace))
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr1(1, 10);
    std::uniform_int_distribution<> distr2(1, 40);

    int randomNumberContext = distr1(gen);
    int randomNumberISR = distr2(gen);
    auto [activity, duration_intr] = parse_trace(trace);

    /******************ADD YOUR SIMULATION CODE HERE*************************/

    /*
    Breakdown of activities:
    CPU: Simulate CPU activity for the specified duration. This will involve calling sleep()
    or sleep_for using crono and thread libraries.

    SYSCALL: Handle a system call. Steps that need to be taken:
      1. Switch to kernel mode
      2. Save the current state of the CPU
      3. Lookup interrupt vector table to find the address of the ISR for system calls
      4. Jump to the ISR address and execute the ISR code
      5. IRET (interrupt return)

    */
    if (activity == "CPU")
    {
      std::cout << timer << ", " << duration_intr << ", handling CPU activity \n";
      timer += duration_intr;
    }
    else if (activity == "SYSCALL")
    {
      auto [execution, time] = intr_boilerplate(timer, duration_intr, randomNumberContext, vectors);
      std::cout << execution;                                                                                                          // gives obtained ISR address
      timer = time;                                                                                                                    // updating running timer with new time after interupts
      int device_time = delays[duration_intr - 1];                                                                                     // taking in device delay from table
      std::cout << timer << ", " << randomNumberISR << ", call device driver (includes delay of " << device_time << " from device)\n"; // includes device delay from table
      timer += device_time;
      std::cout << timer << ", " << 1 << ", IRET\n";
      timer += 1;
    }
    else if (activity == "END_IO")
    {
      int device_time = delays[duration_intr - 1];
      std::cout << timer << ", " << device_time << ", End of I/O " << duration_intr << ": interrupt\n";
      timer += device_time;
    }
    else
    {
      std::cout << "Unknown activity\n";
    }

    /************************************************************************/
  }

  input_file.close();

  write_output(execution);

  return 0;
}
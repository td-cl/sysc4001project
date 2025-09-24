/**
 *
 * @file interrupts.cpp
 * @author Trac-Duy Chu-Le 101220669, Zachary Dredge 101197514
 *
 */

#include <interrupts.hpp>

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

  /******************************************************************/

  // parse each line of the input trace file
  while (std::getline(input_file, trace))
  {
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
      std::cout << "Handling CPU activity\n";
    }
    else if (activity == "SYS_CALL")
    {
      std::cout << "Handling system call\n";
    }
    else if (activity == "END_IO")
    {
      std::cout << "Handling end of I/O\n";
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
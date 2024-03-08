#include <iostream>
#include <vector>
#include <random> // random number generator
#include <map> // maps 
#include <algorithm> // find_if 


// the Process class
class Process {
public:
    int id; // Unique identifier for the process
    std::vector<int> lotteryTickets; // Stores the lottery tickets assigned to the process

    // Constructor 
    Process(int id) : id(id) {}

    // method to allocate a lottery ticket to this process
    void allocateTicket(int ticket) {
        lotteryTickets.push_back(ticket); // Adds the ticket to the process's list of tickets
    }
};

// the Scheduler class
class Scheduler {
private:
    std::vector<Process> processes; // Stores processes managed by Scheduler
    std::map<int, int> ticketToProcessMap; // Maps lottery tickets to process IDs
    int ticketCount = 0; // Tracks the total number of lottery tickets allocated

    // Random number generator, seeded with a random device
    std::mt19937 rng{std::random_device{}()};

public:
    // Adds a process to the scheduler
    void addProcess(Process process) {
        processes.push_back(process); // Inserts the process into the list of managed processes
    }

    // Allocates lottery tickets to all processes managed by the scheduler
    void allocateLotteryTickets() {
        for (auto& process : processes) { // Iterates over all processes
            // Generates a random number of tickets to allocate to the process, between 1 and 10
            int tickets = std::uniform_int_distribution<int>(1, 3)(rng);
            // Allocates the tickets
            for (int i = 0; i < tickets; ++i) { 
                // Increments ticketCount and assigns a new ticket
                process.allocateTicket(++ticketCount); 
                // Maps the new ticket to the process's ID
                ticketToProcessMap[ticketCount] = process.id; 
            }
            
        }
    }

    // Select the next process to run based on the lottery scheduling algorithm
    Process selectNextProcess() {
        // Randomly selects a winning ticket from the total tickets allocated
        int winningTicket = std::uniform_int_distribution<int>(1, ticketCount)(rng);
        // Find the ID of the process that owns the winning ticket
        int winningProcessId = ticketToProcessMap[winningTicket];
        // Searches for the process with the winning ID
        auto it = std::find_if(processes.begin(), processes.end(), [winningProcessId](const Process& process) {
            return process.id == winningProcessId; // Predicate to find the process with the winning ID
        });
        if (it != processes.end()) {
            return *it; // Returns the process with the winning ticket
        } else {
            throw std::runtime_error("Process not found for winning ticket."); 
            // Throws an exception if not found
        }
    }
};

int main() {
    Scheduler scheduler; // Creates an instance of the Scheduler

    // Adds and allocates tickets to 3 processes
    for (int i = 1; i <= 3; ++i) {
        Process process(i); // Creates a process with a unique ID
        scheduler.addProcess(process); // Adds the process to the scheduler
    }

    scheduler.allocateLotteryTickets(); // Allocates lottery tickets to all processes

    // Selects the next process to run based on the lottery and prints its ID
    Process nextProcess = scheduler.selectNextProcess();
    std::cout << "Process " << nextProcess.id << " wins the lottery! " << std::endl;

    return 0; 
}
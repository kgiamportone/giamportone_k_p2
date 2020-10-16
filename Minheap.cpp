#include "Minheap.h"

using namespace std;

int Contestant::getID() {
    return this->id;
}

int Contestant::getPoints() {
    return this->points;
}
/*
Minheap::Minheap(int n) {
    this->max_size = n;
    latest_pos = 0; // keeps track of most recent position inserted in heap
    contestants = NULL; // 'new' yes or no???
    handle = NULL;
    // initialize handle
    for (int i = 0; i < n; i++) {
        handle[i] = -1;
    }

    // initialize heap?
    for (int i = 0; i < n; i++) {
        contestants[i] = new Contestant(-1, -123); // default values
    }
}
int Minheap::initializeArrays() {
    contestants = Contestant[5];
    handle = int[5];
    return 1;
}

*/
/*
Minheap::~Minheap() {
    for (int i = 0; i < max_size; i++) {
        delete contestants[i];
    }
    delete[] contestants;
}
*/
int Minheap::getMaxSize() {
    return this->max_size;
}

void Minheap::maintainHeap() { // FIX THIS FOR NULL elements
    // replace "this.max_size" with max index inserted so far

    // IF latest_pos = 1 OR 0 SPECIAL CASE??
    for (int i = this->latest_pos; i >= 1; i--) {
        if (i*2 <= this->latest_pos) { // check left of node
            if (this->contestants[i].getPoints() > this->contestants[i*2].getPoints()) {
                Contestant temp = contestants[i];
                contestants[i] = contestants[i*2];
                contestants[i*2] = temp;
            }
        }
        if ((i*2)+1 <= this->latest_pos) { // check right of node
            if (this->contestants[i].getPoints() > this->contestants[(i*2)+1].getPoints()) {
                Contestant temp = contestants[i];
                contestants[i] = contestants[(i*2)+1];
                contestants[(i*2)+1] = temp;
            }
        }
    }
    // update position in handle
    for (int i = 1; i < this->max_size; i++) {
        handle[contestants[i].getID()]= i;
    }
}

// -------------------------HEAP FUNCTIONS--------------------------------
void Minheap::findContestant(int k, FILE * output) {
    // print “Contestant <k> is in the extended heap with score <s>.”
    if (k >= this->max_size) { // ID too high to be in heap
        // should NEVER happen
        printf("Find Fail: ID is too great to be in heap\n");
    }
    // printf("Handle[1] = %d\n", handle[1]);
    // printf("Handle[2] = %d\n", handle[2]);
    // printf("Handle[3] = %d\n", handle[3]);
    // printf("Handle[k] = %d\n", handle[k]);
    if (handle[k] == -1) { // not in array
        fprintf(output, "Contestant <%d> is not in the extended heap.\n", k);
        return;
    }
    else { // in array
        fprintf(output, "Contestant <%d> is in the extended heap with score <%d>.\n", contestants[handle[k]].id, contestants[handle[k]].points);
    }

}

void Minheap::insertContestant(int id, int score, FILE * output) {
    // insert into correct position in heap
    // insert into position id handle
    // fix heap order
    if (id >= max_size) {
        printf("Insert Fail 1: Index is too high to insert into array\n");
        return;
    }
    if (latest_pos == max_size - 1) {
        printf("Insert Fail 2\n");
        fprintf(output, "Contestant <%d> could not be inserted because the extended heap is full.\n", id);
        return;
    }
    if (handle[id] != -1) {
        printf("Insert Fail 3\n");
        fprintf(output, "Contestant <%d> is already in the extended heap: cannot insert.\n", id);
        return;
    }
    else {
        Contestant new_contestant = Contestant(id, score);
        latest_pos++;
        contestants[latest_pos] = new_contestant;
        handle[id] = latest_pos;
        //maintainHeap();
        fprintf(output, "Contestant <%d> inserted with initial score <%d>.\n", id, score);
        printf("Insert Success!\n");
    }
}

void Minheap::eliminateWeakest(FILE * output) { // TODO
    if (latest_pos == 0) {
        fprintf(output, "No contestant can be eliminated since the extended heap is empty.\n");
        return;
    }
    Contestant eliminated = contestants[1];
    contestants[1] = contestants[latest_pos];
    handle[contestants[1].id] = 1;
    contestants[latest_pos] = Contestant(-1, -123);
    handle[eliminated.id] = -1;
    latest_pos--; // decrement # of elements in min_queue
    fprintf(output, "Contestant <%d> with current lowest score <%d> eliminated.\n", eliminated.id, eliminated.points);
}

void Minheap::earnPoints(int id, int points_to_add, FILE * output) {
    // first search for id
    if (handle[id] == -1) { // not in array
        fprintf(output, "Contestant <%d> is not in the extended heap.\n", id);
    }
    else { // in array
        contestants[handle[id]].points += points_to_add;
        fprintf(output, "Contestant <%d>’s score increased by <%d> points to <%d>.\n", id, points_to_add, contestants[handle[id]].points);
    }
}

void Minheap::losePoints(int id, int points_to_lose, FILE * output) {
    if (handle[id] == -1) { // not in array
        fprintf(output, "Contestant <%d> is not in the extended heap.\n", id);
    }
    else { // in array
        contestants[handle[id]].points -= points_to_lose;
        fprintf(output, "Contestant <%d>’s score decreased by <%d> points to <%d>.\n", id, points_to_lose, contestants[handle[id]].points);
    }
}

void Minheap::showContestants(FILE * output) {
    for (int i = 1; i <= this->latest_pos; i++) {
        fprintf(output, "Contestant <%d> in extended heap location <%d> with score <%d>.\n", contestants[i].id, i, contestants[i].points);
    }
}

void Minheap::showHandles(FILE * output) {
    for (int i =1; i < this->max_size; i++) {
        if (handle[i] == -1) { // not in array
            fprintf(output, "There is no Contestant <%d> in the extended heap: handle[<%d>] = -1.\n", i, i);
        }
        else { // in array
            fprintf(output, "Contestant <%d> stored in extended heap location <%d>.\n", i, handle[i]);
        }
    }
}

void Minheap::showLocation(int k, FILE * output) {
    if (handle[k] == -1) { // not in array
        fprintf(output, "There is no Contestant <%d> in the extended heap: handle[<%d>] = -1.\n", k, k);
    }
    else { // in array
        fprintf(output, "Contestant <%d> stored in extended heap location <%d>.\n", k, handle[k]);
    }
}

void Minheap::crownWinner(FILE * output) {
    if (latest_pos == 0) {
        fprintf(output, "No contestant can be eliminated since the extended heap is empty.\n");
        return;
    }
    if (latest_pos == 1) {
        fprintf(output, "Contestant <%d> wins with score <%d>!\n", contestants[1].id, contestants[1].points);
        contestants[1] = Contestant(-1, -123);
        return;
    }
    while (latest_pos > 1) {
        // Contestant eliminated = contestants[1];
        contestants[1] = contestants[latest_pos];
        contestants[latest_pos] = Contestant(-1, -123);
        latest_pos--; // decrement # of elements in min_queue
        maintainHeap();
    }
    fprintf(output, "Contestant <%d> wins with score <%d>!\n", contestants[1].id, contestants[1].points);
    contestants[1] = Contestant(-1, -123);
}
/* NOTES!!!!!!
Erase from front of vector:
topPriorityRules.erase(topPriorityRules.begin());
POOR RUNTIME!
option 2:
nums.front() = nums.back
nums.pop_back
    makes front equal to back element (like remove max from heap)
    pops back (which is priority element)

Left child = arr[i * 2]
Right child = arr[(i * 2) + 1]
*/

int main(int argc, char *argv[]) {
    // ./program2 = argv[0]
    // input file = argv[1]
    // output file = argv[2]

    // File IO
    FILE * input_file;
    input_file = fopen(argv[1], "r");
    FILE * output_file;
    output_file = fopen(argv[2], "w");
    // get num contestants
    int max_array_size;
    fscanf(input_file, "%d", &max_array_size);
    printf("Max array size is %d\n", max_array_size);

    // heap object
    Minheap min_queue = Minheap(max_array_size);

    // main while loop to read line by line each operation
    char line[100];
    while (fgets(line, 100, input_file) != NULL) {
        // function name and parameters
        char func[30];
        int param1;
        int param2;

        strtok(line, "\n");
        string line_str = line;
        // Get Rid Of
        //string first_word = line_str.substr(0, line_str.find(" "));

        // FIRST: print line (function from input) to output
        fprintf(output_file, "%s\n", line);
        // SECOND: check which function is to be called and execute
        if (line_str.find("findContestant") != string::npos) {
            sscanf(line, "%s %*[<]%d%*[>]", func, &param1);
            printf("Calling %s with ID=%d\n", func, param1);
            // call findContestant
            min_queue.findContestant(param1, output_file);
        }
        else if (line_str.find("insertContestant") != string::npos) {
            sscanf(line, "%s %*[<]%d%*[>] %*[<]%d%*[>]", func, &param1, &param2);
            printf("Calling %s with ID=%d and points=%d\n", func, param1, param2);
            // call insertContestant
            min_queue.insertContestant(param1, param2, output_file);
        }
        else if (line_str.find("eliminateWeakest") != string::npos) {
            printf("Calling eliminateWeakest\n");
            // call findContestant
            min_queue.eliminateWeakest(output_file);
        }
        else if (line_str.find("earnPoints") != string::npos) {
            sscanf(line, "%s %*[<]%d%*[>] %*[<]%d%*[>]", func, &param1, &param2);
            printf("Calling %s with ID=%d and points=%d\n", func, param1, param2);
            // call earnPoints
            min_queue.earnPoints(param1, param2, output_file);
        }
        else if (line_str.find("losePoints") != string::npos) {
            sscanf(line, "%s %*[<]%d%*[>] %*[<]%d%*[>]", func, &param1, &param2);
            printf("Calling %s with ID=%d and points=%d\n", func, param1, param2);
            // call losePoints
            min_queue.losePoints(param1, param2, output_file);
        }
        else if (line_str.find("showContestants") != string::npos) {
            printf("Calling showContestants\n");
            // call showContestants
            min_queue.showContestants(output_file);
        }
        else if (line_str.find("showHandles") != string::npos) {
            printf("Calling showHandles\n");
            // call showHandles
            min_queue.showHandles(output_file);
        }
        else if (line_str.find("showLocation") != string::npos) {
            sscanf(line, "%s %*[<]%d%*[>]", func, &param1);
            printf("Calling %s with ID=%d\n", func, param1);
            // call showLocation
            min_queue.showLocation(param1, output_file);
        }
        else if (line_str.find("crownWinner") != string::npos) {
            printf("Calling crownWinner\n");
            // call crownWinner
            min_queue.crownWinner(output_file);
        }
        else {
            printf("INVALID FUNCTION CALL\n");
            printf("Line = %s\n", line);
        }
        // MAINTAIN HEAP AFTER EACH OPERATION
        // Contestant person = Contestant(1, 50);
        // printf("Points %d\n", person.getPoints());
        min_queue.maintainHeap();

        // printf("%s\n", first_word.c_str());
        // printf("%s", line_str.c_str());
    }
    fclose(input_file);
    fclose(output_file);
    // delete values from Minheap

    // delete min_queue;
}

#include <getopt.h>
#include <stdio.h>

#include <memory.h>
#include <interconnect.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <assert.h>
#include <stdbool.h>

#include "../central_sv_files/port_define.h"

// #define VERBOSE

typedef enum _bus_req_state
{
    NONE,
    QUEUED,
    TRANSFERING_CACHE,
    TRANSFERING_MEMORY,
    WAITING_CACHE,
    WAITING_MEMORY
} bus_req_state;

typedef struct _bus_req {
    bus_req_type brt;
    bus_req_state currentState;
    uint64_t addr;
    int procNum;
    uint8_t shared;
    uint8_t data;
    uint8_t dataAvail;
    struct _bus_req* next;
} bus_req;

bus_req* pendingRequest = NULL;
bus_req** queuedRequests;
interconn* self;
coher* coherComp;
memory* memComp;

int CADSS_VERBOSE = 0;
int processorCount = 1;

bus_req* pendingCacheTransferRequests = NULL;
bus_req* lastCacheTransferRequest = NULL;

#define PORT PORT_RING
#define SERVER_ADDR "127.0.0.1"

// #define VERBOSE

int sockfd;

static const char* req_state_map[] = {
    [NONE] = "None",
    [QUEUED] = "Queued",
    [TRANSFERING_CACHE] = "Cache-to-Cache Transfer",
    [TRANSFERING_MEMORY] = "Memory Transfer",
    [WAITING_CACHE] = "Waiting for Cache",
    [WAITING_MEMORY] = "Waiting for Memory",
};

static const char* req_type_map[]
    = {[NO_REQ] = "None", [BUSRD] = "BusRd",   [BUSWR] = "BusRdX",
       [DATA] = "Data",   [SHARED] = "Shared", [MEMORY] = "Memory"};



const int CACHE_DELAY = 10; // sure I Guess kind of inaccurate though considering probably should be 2 or 3 cycles
const int CACHE_TRANSFER = 100;

void registerCoher(coher* cc);
void busReq(bus_req_type brt, uint64_t addr, int procNum);
int busReqCacheTransfer(uint64_t addr, int procNum);
void printInterconnState(void);
void interconnNotifyState(void);

void print_cache_list(char *src) {
    #ifdef VERBOSE
    printf("List printout %s\n", src);
    bus_req *req = pendingCacheTransferRequests;
    bus_req *prev = NULL;
    while (req != NULL) {
        printf("addr: %i ",req->addr);
        printf("procNum: %i\n",req->procNum);
        prev = req;
        req = req->next;
    }
    printf("%li %li\n",lastCacheTransferRequest,prev);
    assert(lastCacheTransferRequest == prev);
    printf("Finished\n");
    #endif
}

// Helper methods for per-processor request queues.
static void enqBusRequest(bus_req* pr, int procNum)
{
    bus_req* iter;

    // No items in the queue.
    if (!queuedRequests[procNum])
    {
        queuedRequests[procNum] = pr;
        return;
    }

    // Add request to the end of the queue.
    iter = queuedRequests[procNum];
    while (iter->next)
    {
        iter = iter->next;
    }

    pr->next = NULL;
    iter->next = pr;
}

static bus_req* deqBusRequest(int procNum)
{
    bus_req* ret;

    ret = queuedRequests[procNum];

    // Move the head to the next request (if there is one).
    if (ret)
    {
        queuedRequests[procNum] = ret->next;
    }
    
    return ret;
}

void enqCacheRequest(bus_req *req) {
    if (lastCacheTransferRequest) {
        lastCacheTransferRequest->next = req;
        lastCacheTransferRequest = req;
    } else {
        assert(!pendingCacheTransferRequests);
        pendingCacheTransferRequests = req;
        lastCacheTransferRequest = req;
    }
    req->next = NULL;
    // printf("Pointer %li\n",req);
    print_cache_list("enqCacheReq");
}

bus_req *removeCacheRequest(int procNum, long int addr) {
    bus_req *req = pendingCacheTransferRequests;
    bus_req *prev = NULL;
    while (req) {
        if (req->procNum == procNum && req->addr == addr) {
            if (prev) {
                prev->next = req->next;
            } else {
                pendingCacheTransferRequests = req->next;
            }
            if (lastCacheTransferRequest == req)
                lastCacheTransferRequest = prev;
            // lastCacheTransferRequest = req->next;
            print_cache_list("removeCacheRequest");
            return req;
        }
        prev = req;
        req = req->next;
    }
    return NULL;
    // assert(0);
}

static int busRequestQueueSize(int procNum)
{
    int count = 0;
    bus_req* iter;

    if (!queuedRequests[procNum])
    {
        return 0;
    }

    iter = queuedRequests[procNum];
    while (iter)
    {
        iter = iter->next;
        count++;
    }

    return count;
}

interconn* init(inter_sim_args* isa)
{
    int op;

    while ((op = getopt(isa->arg_count, isa->arg_list, "v")) != -1)
    {
        switch (op)
        {
            default:
                break;
        }
    }

    queuedRequests = malloc(sizeof(bus_req*) * processorCount);
    for (int i = 0; i < processorCount; i++)
    {
        queuedRequests[i] = NULL;
    }

    // pendingCacheTransferRequests = malloc(sizeof(bus_req*) * processorCount);
    // for (int i = 0; i < processorCount; i++)
    // {
    //     pendingCacheTransferRequests[i] = NULL;
    // }

    self = malloc(sizeof(interconn));
    self->busReq = busReq;
    self->registerCoher = registerCoher;
    self->busReqCacheTransfer = busReqCacheTransfer;
    self->si.tick = tick;
    self->si.finish = finish;
    self->si.destroy = destroy;

    memComp = isa->memory;
    memComp->registerInterconnect(self);

    // Connect to already running SV process

    struct sockaddr_in server_addr;
    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        assert(false);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        assert(false);
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        assert(false);
    }

    // command reset
    if (send(sockfd, "reset\n", strlen("reset\n"), 0) == -1) {
        perror("send");
        assert(false);
    }
    // printf("\t\tSent reset, waiting for response\n");
    // printf("\t\tProcessor count: %i\n",processorCount);
    char buffer[1024] = {0};
    if (recv(sockfd, buffer, sizeof(buffer), 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    return self;
}

int countDown = 0;
int lastProc = 0; // for round robin arbitration
int waitOnCacheTransfer = 0;

void registerCoher(coher* cc)
{
    coherComp = cc;
}


void memReqCallback(int procNum, uint64_t addr)
{
    if (!pendingRequest)
    {
        return;
    }

    if (addr == pendingRequest->addr && procNum == pendingRequest->procNum)
    {
        pendingRequest->dataAvail = 1;
    }
}

void busReq(bus_req_type brt, uint64_t addr, int procNum)
{   
    // printf("\t\tProcessor count: %i\n",processorCount);
    // printf("Bus request %s\n",req_type_map[brt]);
    if (pendingRequest == NULL)
    {
        assert(brt != SHARED);

        bus_req* nextReq = calloc(1, sizeof(bus_req));
        nextReq->brt = brt;
        nextReq->currentState = WAITING_CACHE; // go look in the cache and see if we own it? 
        nextReq->addr = addr;
        nextReq->procNum = procNum;
        nextReq->dataAvail = 0;

        pendingRequest = nextReq;
        countDown = CACHE_DELAY;



        return;
    }
    else if (brt == SHARED && pendingRequest->addr == addr) // I don't think we actually do anything about this right now?
    {
        pendingRequest->shared = 1;
        return;
    }
    else if (brt == DATA && pendingRequest->addr == addr)
    {
        assert(pendingRequest->currentState == WAITING_MEMORY);
        pendingRequest->data = 1;
        pendingRequest->brt = DATA; // todo ???
        pendingRequest->currentState = TRANSFERING_CACHE;
        // TODO place these into wrapper functions
        if (send(sockfd, "cacheTransfer\n", strlen("cacheTransfer\n"), 0) == -1) {
            perror("send");
            assert(false);
        }
        // printf("\t\tSent tick, waiting for response\n");
        char buffer[1024] = {0};
        if (recv(sockfd, buffer, sizeof(buffer), 0) == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        char message[1024];
        sprintf(message, "brt: %i, addr: %li, procNumSource: %i, procNumDest: %i\n", brt, addr, procNum, pendingRequest->procNum);
        // printf("Sending %s\n",message);
        if (send(sockfd, message, strlen(message), 0) == -1) {
            perror("send");
            assert(false);
        }
        // countDown = 1; // Another processor called busReq from its coherence engine and now is working on sending it - we want to more accurately simulate this

        // if (pendingCacheTransferRequests) {
        //     assert(lastCacheTransferRequest);
        //     lastCacheTransferRequest->next = pendingRequest;
        //     // lastCacheTransferRequest = pendingRequest;""
        //     // pendingRequest->next = NULL; TODO should this update happen here or elsewhere
        //     // countDown = 0;
        // } else {
        //     pendingCacheTransferRequests = pendingRequest;
        //     // lastCacheTransferRequest = pendingRequest;
        // }
        enqCacheRequest(pendingRequest);
        // printf("Dest: %i\n",pendingRequest->procNum);
        pendingRequest = NULL;
        waitOnCacheTransfer++;
        countDown = 0;
        print_cache_list("busReq");

        return;
    }
    else
    {
        assert(brt != SHARED);

        bus_req* nextReq = calloc(1, sizeof(bus_req));
        nextReq->brt = brt;
        nextReq->currentState = QUEUED;
        nextReq->addr = addr;
        nextReq->procNum = procNum;
        nextReq->dataAvail = 0;

        enqBusRequest(nextReq, procNum);
    }
}

int tick()
{

    memComp->si.tick();

    if (send(sockfd, "tick\n", strlen("tick\n"), 0) == -1) {
        perror("send");
        assert(false);
    }
    // printf("\t\tSent tick, waiting for response\n");
    
    // int cacheTransferFinished = 0;
    long int addr;
    int received;
    bool finished = false;
    // printf("\t\tC Program Received '%s'\n", buffer);
    // char *str_p = buffer;
    // printf("Hello world1\n");
    while (!finished) {
        char buffer[1024] = {0};
        if (recv(sockfd, buffer, sizeof(buffer), 0) == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        bool buffer_finished = false;
        char *ptr = buffer;
        while (!buffer_finished) {
        sscanf(ptr, "ack received: %i %li\n", &received, &addr); // TODO this needs some notion of address
        #ifdef VERBOSE
        if (received != -1)
            printf("Received = %s\n",buffer);
        #endif
        if (received == -1) 
            finished = true;
        else {
            #ifdef VERBOSE
            printf("\t\tC Program Received '%s'\n", buffer);
            #endif
            // cacheTransferFinished = 1;
            
            // buffer = strchr(str_p,'\n') + 1;
            // bus_req* req = pendingCacheTransferRequests;
            // bus_req* prev = NULL;
            // bool removed = false;
            // printf("Searching list for %i, %li\n", received, addr);
            print_cache_list("Pre removal");
            bus_req *req = removeCacheRequest(received,addr);
            assert(req);
            bus_req_type brt = req->brt; // how does the processor get notified of this completion
            if (req->shared == 1)
                brt = SHARED;
            coherComp->busReq(brt, req->addr,
                        req->procNum); // watt is this
            waitOnCacheTransfer--;
            interconnNotifyState();
            free(req);
            print_cache_list("Post removal");
            // printf("Pending: %li\n",pendingCacheTransferRequests);
            // while (req) {
            //     if (req->procNum == received && req->addr == addr) {
            //         removed = true;
            //         bus_req_type brt = req->brt; // how does the processor get notified of this completion
            //         if (req->shared == 1)
            //             brt = SHARED;
            //         coherComp->busReq(brt, req->addr,
            //                     req->procNum); // watt is this
            //         waitOnCacheTransfer--;
            //         // TODO wrap this in some helper functions
            //         if (prev)
            //             prev->next = req->next;
            //         else
            //             pendingCacheTransferRequests = req->next;
            //         if (req->next)
            //             if (!req->next->next)
            //                 lastCacheTransferRequest = req->next;
            //         else
            //             lastCacheTransferRequest = prev;
            //         interconnNotifyState();
            //         free(req);
            //         print_cache_list();
            //         break;
            //     }
            //     prev = req;
            //     req = req->next;
            // }

            // if (!removed) {
            //     printf("That's not good oh what if memory repl no");
            //     assert(0);
            // }
        }
        while (*ptr != '\n' && *ptr != '\0') {
            ptr++;
        }
        ptr++;
        if (*ptr == '\0')
            buffer_finished = true;
    }
    }
    // printf("Hello world3\n");
    // TODO handle if it is ack or informing us of something, handle appropriately 

    if (self->dbgEnv.cadssDbgWatchedComp && !self->dbgEnv.cadssDbgNotifyState)
    {
        printInterconnState();
    }

    if (countDown > 0)
    {
        assert(pendingRequest != NULL);
        countDown--;

        // if (waitOnCacheTransfer) {
        //     countDown = (cacheTransferFinished) ? 0 : 1;
        // }

        // If the count-down has elapsed (or there hasn't been a
        // cache-to-cache transfer, the memory will respond with
        // the data.
        if (pendingRequest->dataAvail)
        {
            pendingRequest->currentState = TRANSFERING_MEMORY;
            countDown = 0;
        }

        if (countDown == 0)
        {
            if (pendingRequest->currentState == WAITING_CACHE)
            {
                // Make a request to memory.
                countDown
                    = memComp->busReq(pendingRequest->addr,
                                      pendingRequest->procNum, memReqCallback);

                pendingRequest->currentState = WAITING_MEMORY;

                // The processors will snoop for this request as well.
                for (int i = 0; i < processorCount; i++)
                {
                    if (pendingRequest) {
                        if (pendingRequest->procNum != i)
                        {
                            coherComp->busReq(pendingRequest->brt,
                                            pendingRequest->addr, i);
                        }
                    } else {
                        assert(lastCacheTransferRequest);
                        assert(countDown == 0);
                    }
                }
                
                // this is the case where it was snooped i think
                // if (pendingRequest->data == 1)
                // {
                //     pendingRequest->brt = DATA;
                // }
            }
            else if (pendingRequest->currentState == TRANSFERING_MEMORY)
            {
                bus_req_type brt
                    = (pendingRequest->shared == 1) ? SHARED : DATA;
                coherComp->busReq(brt, pendingRequest->addr,
                                  pendingRequest->procNum); // coher gets notified here of completion, triggers call to main processor

                interconnNotifyState();
                free(pendingRequest);
                pendingRequest = NULL;
            }
            else if (pendingRequest->currentState == TRANSFERING_CACHE)
            {
                assert(0);
                bus_req_type brt = pendingRequest->brt; // how does the processor get notified of this completion
                if (pendingRequest->shared == 1)
                    brt = SHARED;

                coherComp->busReq(brt, pendingRequest->addr,
                                  pendingRequest->procNum);

                interconnNotifyState();
                free(pendingRequest);
                pendingRequest = NULL;
                waitOnCacheTransfer--;
            }
        }
    }
    else if (countDown == 0) // select next new candidate!
    {
        for (int i = 0; i < processorCount; i++)
        {
            int pos = (i + lastProc) % processorCount;
            if (queuedRequests[pos] != NULL)
            {
                pendingRequest = deqBusRequest(pos);
                countDown = CACHE_DELAY;
                pendingRequest->currentState = WAITING_CACHE;

                lastProc = (pos + 1) % processorCount;
                break;
            }
        }
    }

    return 0;
}

void printInterconnState(void)
{
    if (!pendingRequest)
    {
        return;
    }

    printf("--- Interconnect Debug State (Processors: %d) ---\n"
           "       Current Request: \n"
           "             Processor: %d\n"
           "               Address: 0x%016lx\n"
           "                  Type: %s\n"
           "                 State: %s\n"
           "         Shared / Data: %s\n"
           "                  Next: %p\n"
           "             Countdown: %d\n"
           "    Request Queue Size: \n",
           processorCount, pendingRequest->procNum, pendingRequest->addr,
           req_type_map[pendingRequest->brt],
           req_state_map[pendingRequest->currentState],
           pendingRequest->shared ? "Shared" : "Data", pendingRequest->next,
           countDown);

    for (int p = 0; p < processorCount; p++)
    {
        printf("       - Processor[%02d]: %d\n", p, busRequestQueueSize(p));
    }
}

void interconnNotifyState(void)
{
    if (!pendingRequest)
        return; // ????

    if (self->dbgEnv.cadssDbgExternBreak)
    {
        printInterconnState();
        raise(SIGTRAP);
        return;
    }

    if (self->dbgEnv.cadssDbgWatchedComp && self->dbgEnv.cadssDbgNotifyState)
    {
        self->dbgEnv.cadssDbgNotifyState = 0;
        printInterconnState();
    }
}

// Return a non-zero value if the current request
// was satisfied by a cache-to-cache transfer.
int busReqCacheTransfer(uint64_t addr, int procNum)
{
    // assert(pendingRequest);

    // if (addr == pendingRequest->addr && procNum == pendingRequest->procNum) {
    //     // assert(0);
    //     return (pendingRequest->currentState == TRANSFERING_CACHE);
    // }

    bus_req *req = pendingCacheTransferRequests;
    while (req) {
        if (addr == req->addr && procNum == req->procNum) {
            return 1;
        }
        req = req->next;
    }

    return 0;
}

int finish(int outFd)
{   
    memComp->si.finish(outFd);
    return 0;
}

int destroy(void)
{
    if (send(sockfd, "quit\n", strlen("quit\n"), 0) == -1) {
        perror("send");
        assert(false);
    }
    close(sockfd);
    memComp->si.destroy();
    return 0;
}

#include <iostream>
#include <array>

enum class State_e
{
    UNKNOWN,
    STATE1,
    STATE2,
    STATE3
};

typedef struct
{
    const char* name;
    void (*before)();
    State_e (*state_function)();
    void (*after)();
}state_t;

std::array state_table = 
{
    state_t{"",         [](void){}, 
                        [](void){return State_e::STATE1;}, 
                        [](void){}},
    state_t{"state1",   [](void){printf("pre:state1\n");}, 
                        [](void){printf("state1\n"); return State_e::STATE2;}, 
                        [](void){printf("after:state1\n");}},
    state_t{"state2",   [](void){printf("pre:state2\n");}, 
                        [](void){printf("state2\n"); return State_e::STATE3;}, 
                        [](void){printf("after:state2\n");}},
    state_t{"state3",   [](void){printf("pre:state3\n");}, 
                        [](void){printf("state3\n"); return State_e::STATE1;}, 
                        [](void){printf("after:state3\n"); exit(0);}},                        
};


int main()
{
    static State_e state = State_e::UNKNOWN, prev_state = State_e::UNKNOWN;
    while(true)
    {
        if (prev_state != state)
        {
            state_table[static_cast<int>(prev_state)].after();
            state_table[static_cast<int>(state)].before();
            prev_state = state;
            printf("state name = %s\n", state_table[static_cast<int>(state)].name);
        }
        else
        {
            state = state_table[static_cast<int>(state)].state_function();
        }
    }
    printf("%s\n", state_table[0].name);
}
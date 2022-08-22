#include "Vtop.h"
#include "verilated.h"

#define MOSTCYCLE 2000000
#define MAXOP 9223372036854775807
uint8_t req_valid_flag = 0;
uint8_t has_valid = 1;
uint64_t op_1;
uint64_t op_2;
uint64_t result;
int newest_valid_count = 0;


uint8_t get_req_valid_flag(int count)
{
    if(!has_valid)
    {
        return 0;
    }
    if(rand()%10>7 and count > newest_valid_count)
    {
        /* printf("push a req\n"); */
        has_valid = 0;
        req_valid_flag = 1;
        op_1 = rand()%MAXOP;
        op_2 = rand()%MAXOP;
        return 1;
    }
    return 0;
}

int main(int argc, char** argv, char** env)
{
    srand((unsigned)time(NULL));
	Verilated::mkdir("logs");
	VerilatedContext* contextp = new VerilatedContext;
	contextp->traceEverOn(true);
	contextp->commandArgs(argc, argv);
	Vtop* top = new Vtop{contextp};
    top->rst = 0;
    int count = 0;
	while (count <= MOSTCYCLE && !contextp->gotFinish())
	{
        /* Get the outputs */
/*         printf("result_l_o=%lu\n", top->result_l_o);
        printf("result_h_o=%lu\n", top->result_h_o);
        printf("ready_o=%d\n", top->ready_o);
        printf("valid_o=%d\n", top->valid_o); */
        if(top->valid_o==1 && req_valid_flag==1)
        {
            newest_valid_count = count;
            has_valid = 1;
            result = top->result_l_o;
            req_valid_flag = 0;
            /* printf("=======================\n"); */
            printf("op_1 %lu\n", op_1);
            printf("op_2 %lu\n", op_2);
            printf("result %lu\n", result);
        }
        /* Drive the inputs */
        top->req_valid_i = get_req_valid_flag(count);
        top->block_i = 0;
        top->op_1_i = op_1;
        top->op_2_i = op_2;
        top->sign_op_1_i = 0;
        top->sign_op_2_i = 0;
        top->eval_step();
        /* posedge */
        top->clk = 1;
        top->eval_step();
        contextp->timeInc(1);
        top->eval_step();
        top->eval_end_step();
        top->clk = 0;
        contextp->timeInc(1);
        top->eval();
        count++;
    }
	delete top;
	delete contextp;
	return 0;
}

#include <stdio.h>

void convert(char *input, int *inputb)
{
    for (int i = 0; i < 8; i++)
    {
        if (input[i] == '0')
        {
            inputb[4 * i + 0] = 0;
            inputb[4 * i + 1] = 0;
            inputb[4 * i + 2] = 0;
            inputb[4 * i + 3] = 0;
        }

        else if (input[i] == '1')
        {
            inputb[4 * i + 0] = 0;
            inputb[4 * i + 1] = 0;
            inputb[4 * i + 2] = 0;
            inputb[4 * i + 3] = 1;
        }

        else if (input[i] == '2')
        {
            inputb[4 * i + 0] = 0;
            inputb[4 * i + 1] = 0;
            inputb[4 * i + 2] = 1;
            inputb[4 * i + 3] = 0;
        }

        else if (input[i] == '3')
        {
            inputb[4 * i + 0] = 0;
            inputb[4 * i + 1] = 0;
            inputb[4 * i + 2] = 1;
            inputb[4 * i + 3] = 1;
        }

        else if (input[i] == '4')
        {
            inputb[4 * i + 0] = 0;
            inputb[4 * i + 1] = 1;
            inputb[4 * i + 2] = 0;
            inputb[4 * i + 3] = 0;
        }

        else if (input[i] == '5')
        {
            inputb[4 * i + 0] = 0;
            inputb[4 * i + 1] = 1;
            inputb[4 * i + 2] = 0;
            inputb[4 * i + 3] = 1;
        }

        else if (input[i] == '6')
        {
            inputb[4 * i + 0] = 0;
            inputb[4 * i + 1] = 1;
            inputb[4 * i + 2] = 1;
            inputb[4 * i + 3] = 0;
        }

        else if (input[i] == '7')
        {
            inputb[4 * i + 0] = 0;
            inputb[4 * i + 1] = 1;
            inputb[4 * i + 2] = 1;
            inputb[4 * i + 3] = 1;
        }

        else if (input[i] == '8')
        {
            inputb[4 * i + 0] = 1;
            inputb[4 * i + 1] = 0;
            inputb[4 * i + 2] = 0;
            inputb[4 * i + 3] = 0;
        }

        else if (input[i] == '9')
        {
            inputb[4 * i + 0] = 1;
            inputb[4 * i + 1] = 0;
            inputb[4 * i + 2] = 0;
            inputb[4 * i + 3] = 1;
        }

        else if (input[i] == 'a' || input[i] == 'A')
        {
            inputb[4 * i + 0] = 1;
            inputb[4 * i + 1] = 0;
            inputb[4 * i + 2] = 1;
            inputb[4 * i + 3] = 0;
        }

        else if (input[i] == 'b' || input[i] == 'B')
        {
            inputb[4 * i + 0] = 1;
            inputb[4 * i + 1] = 0;
            inputb[4 * i + 2] = 1;
            inputb[4 * i + 3] = 1;
        }

        else if (input[i] == 'c' || input[i] == 'C')
        {
            inputb[4 * i + 0] = 1;
            inputb[4 * i + 1] = 1;
            inputb[4 * i + 2] = 0;
            inputb[4 * i + 3] = 0;
        }

        else if (input[i] == 'd' || input[i] == 'D')
        {
            inputb[4 * i + 0] = 1;
            inputb[4 * i + 1] = 1;
            inputb[4 * i + 2] = 0;
            inputb[4 * i + 3] = 1;
        }

        else if (input[i] == 'e' || input[i] == 'E')
        {
            inputb[4 * i + 0] = 1;
            inputb[4 * i + 1] = 1;
            inputb[4 * i + 2] = 1;
            inputb[4 * i + 3] = 0;
        }

        else if (input[i] == 'f' || input[i] == 'F')
        {
            inputb[4 * i + 0] = 1;
            inputb[4 * i + 1] = 1;
            inputb[4 * i + 2] = 1;
            inputb[4 * i + 3] = 1;
        }
    }
}

char detType(int opcode[7])
{
    if (opcode[0] == 0 && opcode[1] == 1 && opcode[2] == 1 && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 1 && opcode[6] == 1)
    {
        return 'R'; // R Type
    }

    else if (opcode[0] == 0 && opcode[1] == 0 && opcode[2] == 1 && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 1 && opcode[6] == 1)
    {
        return 'i';
    }

    else if (opcode[0] == 0 && opcode[1] == 0 && opcode[2] == 0 && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 1 && opcode[6] == 1)
    {
        return 'I';
    }

    else if (opcode[0] == 0 && opcode[1] == 1 && opcode[2] == 0 && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 1 && opcode[6] == 1)
    {
        return 'S';
    }

    else if (opcode[0] == 1 && opcode[1] == 1 && opcode[2] == 0 && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 1 && opcode[6] == 1)
    {
        return 'B';
    }

    else if (opcode[0] == 1 && opcode[1] == 1 && opcode[2] == 0 && opcode[3] == 1 && opcode[4] == 1 && opcode[5] == 1 && opcode[6] == 1)
    {
        return 'j'; // jal
    }

    else if (opcode[0] == 1 && opcode[1] == 1 && opcode[2] == 0 && opcode[3] == 0 && opcode[4] == 1 && opcode[5] == 1 && opcode[6] == 1)
    {
        return 'J'; // jalr
    }

    else if (opcode[0] == 0 && opcode[1] == 1 && opcode[2] == 1 && opcode[3] == 0 && opcode[4] == 1 && opcode[5] == 1 && opcode[6] == 1)
    {
        return 'L'; // LUI
    }
}

int power(int base, int index)
{
    int answer = 1;

    for (int i = 0; i < index; i++)
    {
        answer = answer * base;
    }

    return answer;
}

void print_R_inst(int funct7[7], int funct3[3])
{
    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        if (funct7[1] == 0)
        {
            printf("add ");
        }

        else if (funct7[1] == 1)
        {
            printf("sub ");
        }
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 0)
    {
        printf("xor ");
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 0)
    {
        printf("or ");
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 1)
    {
        printf("and ");
    }

    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1)
    {
        printf("sll ");
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 1)
    {
        if (funct7[1] == 0)
        {
            printf("srl ");
        }

        else if (funct7[1] == 1)
        {
            printf("sra ");
        }
    }
}

void R_format(int inputb[32])
{
    int funct3[3];
    int funct7[7];
    int rd[5];
    int rd_num = 0;
    int rs1[5];
    int rs1_num = 0;
    int rs2[5];
    int rs2_num = 0;

    // First determining register numbers:
    for (int i = 0; i < 5; i++)
    {
        rs2[i] = inputb[i + 7];
        rs1[i] = inputb[i + 12];
        rd[i] = inputb[i + 20];
    }

    for (int i = 4; i >= 0; i--)
    {
        rd_num = rd_num + rd[i] * power(2, 4 - i);
        rs1_num = rs1_num + rs1[i] * power(2, 4 - i);
        rs2_num = rs2_num + rs2[i] * power(2, 4 - i);
    }

    // printf("rd = %d rs1 = %d rs2 = %d\n", rd_num, rs1_num, rs2_num);

    for (int i = 0; i < 7; i++)
    {
        funct7[i] = inputb[i];
    }

    for (int i = 0; i < 3; i++)
    {
        funct3[i] = inputb[i + 17];
    }

    print_R_inst(funct7, funct3);
    printf("x%d, x%d, x%d\n", rd_num, rs1_num, rs2_num);
}

int FindingImm(int *imm, int size)
{
    int res = 0;

    if (imm[0] == 0)
    {
        for (int i = 0; i < size - 1; i++)
        {
            res = res + imm[size - 1 - i] * power(2, i);
        }

        return res;
    }

    else if (imm[0] == 1)
    {
        /*
            If negative, then first we should invert all bits,
            then add 1 to the last bit. If it is two, send carry
            over to the next bit.
        */
        for (int i = 0; i < size; i++)
        {
            if (imm[i] == 0)
            {
                imm[i] = 1;
            }

            else if (imm[i] == 1)
            {
                imm[i] = 0;
            }

            else
            {
                printf("Error\n");
            }
        }

        imm[size - 1] = imm[size - 1] + 1;

        for (int i = 0; i < size; i++)
        {
            if (imm[size - 1 - i] == 2)
            {
                imm[size - 1 - i] = 0;
                imm[size - 2 - i] = imm[size - 2 - i] + 1;
            }
        }

        if (imm[0] > 1)
        {
            printf("Error\n");
        }

        for (int i = 0; i < size - 1; i++)
        {
            res = res + imm[size - 1 - i] * power(2, i);
            // printf("%d\t", res);
        }

        return (-res);
    }
}

int findImm(int *imm)
{
    int res = 0;

    if (imm[0] == 0) // Positive
    {
        for (int i = 0; i < 11; i++)
        {
            res = res + imm[11 - i] * power(2, i);
        }

        return res;
    }

    else if (imm[0] == 1)
    {
        /*
            If negative, then first we should invert all bits,
            then add 1 to the last bit. If it is two, send carry
            over to the next bit.
        */
        for (int i = 0; i < 12; i++)
        {
            if (imm[i] == 0)
            {
                imm[i] = 1;
            }

            else if (imm[i] == 1)
            {
                imm[i] = 0;
            }

            else
            {
                printf("Error\n");
            }
        }

        imm[11] = imm[11] + 1;

        for (int i = 0; i < 12; i++)
        {
            if (imm[11 - i] == 2)
            {
                imm[11 - i] = 0;
                imm[10 - i] = imm[10 - i] + 1;
            }
        }

        if (imm[0] > 1)
        {
            printf("Error\n");
        }

        // Now calculating the value of the string.
        for (int i = 0; i < 11; i++)
        {
            res = res + imm[11 - i] * power(2, i);
            // printf("%d\t", res);
        }

        return (-res);
    }
}

void print_i_inst(int funct3[3], int imm[12])
{
    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        printf("addi ");
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 0)
    {
        printf("xori ");
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 0)
    {
        printf("ori ");
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 1)
    {
        printf("andi ");
    }

    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1 && imm[6] == 0)
    {
        printf("slli ");
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 1)
    {
        if (imm[6] == 0)
        {
            printf("srli ");
        }

        else if (imm[6] == 1)
        {
            printf("srai ");
        }
    }
}

void I_format_a(int inputb[32])
{
    int imm[12];
    int rs1[5];
    int funct3[3];
    int rd[5];
    int rd_num = 0;
    int rs1_num = 0;
    int imm_val = 0;
    int I1_imm_val = 0;

    for (int i = 0; i < 12; i++)
    {
        imm[i] = inputb[i];
    }

    for (int i = 0; i < 6; i++)
    {
        I1_imm_val = I1_imm_val + imm[11 - i] * power(2, i);
    }

    for (int i = 0; i < 5; i++)
    {
        rs1[i] = inputb[i + 12];
        rd[i] = inputb[i + 20];
    }

    for (int i = 0; i < 3; i++)
    {
        funct3[i] = inputb[i + 17];
    }

    print_i_inst(funct3, imm);

    // Finding the value of immediate
    imm_val = FindingImm(imm, 12);

    for (int i = 4; i >= 0; i--)
    {
        rd_num = rd_num + rd[i] * power(2, 4 - i);
        rs1_num = rs1_num + rs1[i] * power(2, 4 - i);
    }

    if ((funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 1) || (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1))
    {
        printf("x%d, x%d, %d\n", rd_num, rs1_num, I1_imm_val);
    }
    else
        printf("x%d, x%d, %d\n", rd_num, rs1_num, imm_val);
}

void print_I_inst(int funct3[3])
{
    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        printf("lb ");
    }
    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1)
    {
        printf("lh ");
    }
    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 0)
    {
        printf("lw ");
    }
    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 1)
    {
        printf("ld ");
    }
    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 0)
    {
        printf("lbu ");
    }
    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 1)
    {
        printf("lhu ");
    }
    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 0)
    {
        printf("lwu ");
    }
}

void I_format_b(int inputb[32])
{
    int imm[12];
    int rs1[5];
    int funct3[3];
    int rd[5];
    int rd_num = 0;
    int rs1_num = 0;
    int imm_val = 0;

    for (int i = 0; i < 12; i++)
    {
        imm[i] = inputb[i];
    }

    for (int i = 0; i < 5; i++)
    {
        rs1[i] = inputb[i + 12];
        rd[i] = inputb[i + 20];
    }

    for (int i = 0; i < 3; i++)
    {
        funct3[i] = inputb[i + 17];
    }

    print_I_inst(funct3);

    // Finding the value of immediate
    imm_val = FindingImm(imm, 12);

    for (int i = 4; i >= 0; i--)
    {
        rd_num = rd_num + rd[i] * power(2, 4 - i);
        rs1_num = rs1_num + rs1[i] * power(2, 4 - i);
    }

    printf("x%d, %d(x%d)\n", rd_num, imm_val, rs1_num);
}

void print_S_inst(int funct3[3])
{
    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        printf("sb ");
    }
    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1)
    {
        printf("sh ");
    }
    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 0)
    {
        printf("sw ");
    }
    else if (funct3[0] == 0 && funct3[1] == 1 && funct3[2] == 1)
    {
        printf("sd ");
    }
}

void S_format(int inputb[32])
{
    int imm[12];
    int rs2[5];
    int rs1[5];
    int imm_val;
    int rs2_num = 0;
    int rs1_num = 0;
    int funct3[3];

    for (int i = 0; i < 5; i++)
    {
        rs2[i] = inputb[i + 7];
        rs1[i] = inputb[i + 12];
    }

    for (int i = 0; i < 7; i++)
    {
        imm[i] = inputb[i];
    }

    for (int i = 0; i < 5; i++)
    {
        imm[i + 7] = inputb[i + 20];
    }

    for (int i = 0; i < 3; i++)
    {
        funct3[i] = inputb[i + 17];
    }

    imm_val = FindingImm(imm, 12);

    for (int i = 0; i < 5; i++)
    {
        rs1_num = rs1_num + rs1[4 - i] * power(2, i);
        rs2_num = rs2_num + rs2[4 - i] * power(2, i);
    }

    print_S_inst(funct3);
    printf("x%d, %d(x%d)\n", rs2_num, imm_val, rs1_num);
}

void print_B_inst(int funct3[3])
{
    if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 0)
    {
        printf("beq ");
    }

    else if (funct3[0] == 0 && funct3[1] == 0 && funct3[2] == 1)
    {
        printf("bne ");
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 0)
    {
        printf("blt ");
    }

    else if (funct3[0] == 1 && funct3[1] == 0 && funct3[2] == 1)
    {
        printf("bge ");
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 0)
    {
        printf("bltu ");
    }

    else if (funct3[0] == 1 && funct3[1] == 1 && funct3[2] == 1)
    {
        printf("bgeu ");
    }
}

void B_format(int inputb[32])
{
    int imm[13];
    int rs2[5];
    int rs1[5];
    int funct3[3];
    int imm_val;
    int rs1_num = 0;
    int rs2_num = 0;

    for (int i = 0; i < 5; i++)
    {
        rs2[i] = inputb[i + 7];
        rs1[i] = inputb[i + 12];
    }

    for (int i = 0; i < 3; i++)
    {
        funct3[i] = inputb[i + 17];
    }

    for (int i = 1; i < 7; i++)
    {
        imm[i + 1] = inputb[i];
    }

    for (int i = 0; i < 5; i++)
    {
        imm[i + 8] = inputb[i + 20];
    }

    imm[0] = 0;
    imm[1] = inputb[24];
    imm[12] = 0;

    imm_val = FindingImm(&(*(imm + 1)), 12);

    // for (int i = 0; i < 12; i++)
    // {
    //     printf("%d", *(imm + i + 1));
    // }
    // printf("\n");

    for (int i = 4; i >= 0; i--)
    {
        rs2_num = rs2_num + rs2[i] * power(2, 4 - i);
        rs1_num = rs1_num + rs1[i] * power(2, 4 - i);
    }

    print_B_inst(funct3);
    printf("x%d, x%d, %d\n", rs1_num, rs2_num, imm_val);
}

void lui(int inputb[32])
{
    int rd[5];
    int rd_num = 0;

    for (int i = 0; i < 5; i++)
    {
        rd[i] = inputb[i + 20];
    }

    for (int i = 4; i >= 0; i--)
    {
        rd_num = rd_num + rd[i] * power(2, 4 - i);
    }

    printf("lui x%d, 0x", rd_num);
}

void jal(int inputb[32])
{
    int imm[21];
    int rd[5];
    int imm_val = 0;
    int rd_num = 0;

    imm[0] = inputb[0];
    imm[9] = inputb[11];
    imm[20] = 0;

    for (int i = 0; i < 8; i++)
    {
        imm[i + 1] = inputb[i + 12];
    }

    for(int i = 0; i < 10; i++)
    {
        imm[i + 10] = inputb[i + 1];
    }

    imm_val = FindingImm(imm, 21);

    for (int i = 0; i < 5; i++)
    {
        rd[i] = inputb[i + 20];
    }

    for (int i = 4; i >= 0; i--)
    {
        rd_num = rd_num + rd[i] * power(2, 4 - i);
    }

    if (inputb[0] == 0)
    {
        printf("jal x%d, %d\n", rd_num, imm_val);
    }

    else if (inputb[0] == 1)
    {
        printf("jal x%d, %d\n", rd_num, imm_val);
    }
}

void jalr(int inputb[32])
{
    int imm[21];
    int rs1[5];
    int rd[5];
    int rs1_num = 0;
    int rd_num = 0;
    int imm_val;

    for (int i = 0; i < 12; i++)
    {
        imm[i] = inputb[i];
    }

    for (int i = 0; i < 5; i++)
    {
        rs1[i] = inputb[i + 12];
        rd[i] = inputb[i + 20];
    }

    for (int i = 4; i >= 0; i--)
    {
        rd_num = rd_num + rd[i] * power(2, 4 - i);
        rs1_num = rs1_num + rs1[i] * power(2, 4 - i);
    }

    imm_val = FindingImm(imm, 12);

    printf("jalr x%d, %d(x%d) or jalr x%d, x%d, %d\n", rd_num, imm_val, rs1_num, rd_num, rs1_num, imm_val);
}

int main()
{
    FILE *filePtr;
    filePtr = fopen("inputs.txt", "r");

    char input[8];
    int inputb[32];
    char type;
    char *c;

    while (fgets(input, 7, filePtr) != NULL)
    {
        for (int i = 0; i < 8; i++)
        {
            fscanf(filePtr, "%c", &input[i]);
        }

        printf("%s : ", input);

        convert(input, inputb);

        type = detType(&(*(inputb + 25))); // sending the address of last 6 bits

        if (type == 'R')
        {
            R_format(inputb);
        }

        else if (type == 'i')
        {
            I_format_a(inputb);
        }

        else if (type == 'I')
        {
            I_format_b(inputb);
        }

        else if (type == 'S')
        {
            S_format(inputb);
        }

        else if (type == 'B')
        {
            B_format(inputb);
        }

        else if (type == 'L')
        {
            lui(inputb);
            for (int i = 0; i < 5; i++)
            {
                printf("%c", input[i]);
            }
            printf("\n");
        }

        else if (type == 'j')
        {
            jal(inputb);
        }

        else if (type == 'J')
        {
            jalr(inputb);
        }
    }

    fclose(filePtr);
    return 0;
}
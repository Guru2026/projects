#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>
#include "decode.h"

OperationType check_operation_type(char *);

int main(int argc, char *argv[])
{
    //step1 -> call check_operation_type(argv[1]);
            // print msg
        //-e -> encode
        // declare structure variable EncodeInfo encInfo;
        // check read_and_validate_encode_args(argv, &encInfo) is e_success or not
                // no -> print error msg and return e_failure;
                // yes -> check do_encoding(&encInfo) returning e_success or not
                            // no -> print error msg and stop 
                            // yes -> print success msg and stop
        if(argc<2){
            printf("Usage: ./a.out -e|-d\n");
            return e_failure;
        }
        OperationType op=check_operation_type(argv[1]);
        if(op==e_encode){
            printf("Encoding selected");
            EncodeInfo encInfo;
            if(read_and_validate_encode_args(argv,&encInfo)==e_failure){
                printf("ERROR: Invalid encode arguments\n");
                return e_failure;
            }
            if(do_encoding(&encInfo)==e_failure){
                printf("ERROR: Encoding failed\n");
                return e_failure;
            }
            printf("Encoding completed successfully\n");
        }
        else if(op==e_decode){
            printf("Decoding selected");
            DecodeInfo decInfo;
            if(read_and_validate_decode_args(argv,&decInfo)==e_failure){
                printf("ERROR: Invalid decode arguments\n");
                return e_failure;
            }
            if(do_decoding(&decInfo) == e_failure)
        {
            printf("ERROR: Decoding failed\n");
            return e_failure;
        }
        printf("Decoding completed successfully\n");
    }
        else{
            printf("Unsupported operation\n");
            return e_failure;
        }
        return e_success;
}

OperationType check_operation_type(char *symbol)
{
    //step1 -> check it is -e or -d
         //-e ->return e_encode
            //-d -> return e_decode

            //return e_unsupported
    if(strcmp(symbol,"-e")==0){
        return e_encode;
    }else if(strcmp(symbol,"-d")==0){
        return e_decode;
    }else{
        return e_unsupported;
    }
}

#ifndef _C_HOLDEM_EVALUATOR_WRAPPER_
#define _C_HOLDEM_EVALUATOR_WRAPPER_

#ifdef __cplusplus
extern "C" {
#endif

int32_t evaluate_holdem(const char* board, const char* hands, double *buf, size_t *size);

#ifdef __cplusplus
}
#endif

#endif //_C_HOLDEM_EVALUATOR_WRAPPER_

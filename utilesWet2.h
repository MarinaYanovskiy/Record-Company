#ifndef UTILES_WET2_H
#define UTILES_WET2_H


typedef enum StatusType_t {
  SUCCESS          = 0,
  ALLOCATION_ERROR = 1,
  INVALID_INPUT    = 2,
  FAILURE          = 3,
  ALREADY_EXISTS   = 4,
  DOESNT_EXISTS    = 5
} StatusType;


template<typename T>
class Output_t {
  private:
    const StatusType __status;
    const T __res;
    const bool __is_res;
  public:
    Output_t() : __status(SUCCESS), __res(T()), __is_res(false) { }
    Output_t(StatusType status) : __status(status), __res(T()), __is_res(false) { }
    Output_t(const T res) : __status(SUCCESS), __res(res), __is_res(true) { }

    StatusType status() { return __status; }
    T ans() { return __res; }
    bool is_res() { return __is_res; }
};


#endif
#ifndef X_ERROR_H
#define X_ERROR_H
inline void error(const char *msg)
{
      perror(msg);
//      exit(1);
}
#endif

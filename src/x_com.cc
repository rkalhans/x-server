#include <x_com.h>
#include <x_thd.h>
int
THD::handle_command()
{
  int com_val= this->net_io->buff[0];
  this->command= get_server_command(com_val);
  switch (command)
  {
    case X_COM_SLEEP:
    case X_COM_QUIT:
    case X_COM_INIT_DB:
    case X_COM_QUERY:
    case X_COM_FIELD_LIST:
    case X_COM_CREATE_DB:
    case X_COM_DROP_DB:
    case X_COM_REFRESH:
    case X_COM_SHUTDOWN:
    case X_COM_STATISTICS:
    case X_COM_PROCESS_KILL:
    case X_COM_PING:
    case X_COM_TIME:
    case X_COM_DELAYED_INSERT:
    case X_COM_CHANGE_USER:
    case X_COM_BINLOG_DUMP:
    case X_COM_TABLE_DUMP:
    case X_COM_CONNECT_OUT:
    case X_COM_REGISTER_SLAVE:
    case X_COM_STMT_PREPARE:
    case X_COM_STMT_EXECUTE:
    case X_COM_STMT_SEND_LONG_DATA:
    case X_COM_STMT_CLOSE:
    case X_COM_STMT_RESET:
    case X_COM_SET_OPTION:
    case X_COM_STMT_FETCH:
    case X_COM_DAEMON:
    case X_COM_BINLOG_DUMP_GTID:
      this->command_result= SUCCESS;
      break;
    case X_COM_END:
      this->command_result= FAILURE;
      break;
  }
  this->send_confirmation_to_client();
  return 0;
}

X_COMMAND get_server_command(int com_val)
{
  switch(com_val)
  {
  case 0x00:
    return X_COM_SLEEP;
  case 0x01:
    return X_COM_QUIT;
  case 0x02:
    return X_COM_INIT_DB;
  case 0x03:
    return X_COM_QUERY;
  case 0x04:
    return X_COM_FIELD_LIST;
  case 0x05:
    return X_COM_CREATE_DB;
  case 0x06:
    return X_COM_DROP_DB;
  case 0x07:
    return X_COM_REFRESH;
  case 0x08:
    return X_COM_SHUTDOWN;
  case 0x09:
    return X_COM_STATISTICS;
  case 0x0a:
    return X_COM_PROCESS_KILL;
  case 0x0b:
    return X_COM_PING;
  case 0x0c:
    return X_COM_TIME;
  case 0x0d:
    return X_COM_DELAYED_INSERT;
  case 0x0e:
    return X_COM_CHANGE_USER;
  case 0x0f:
    return X_COM_BINLOG_DUMP;
  case 0x10:
    return X_COM_TABLE_DUMP;
  case 0x11:
    return X_COM_CONNECT_OUT;
  case 0x12:
    return X_COM_REGISTER_SLAVE;
  case 0x13:
    return X_COM_STMT_PREPARE;
  case 0x14:
    return X_COM_STMT_EXECUTE;
  case 0x15:
    return X_COM_STMT_SEND_LONG_DATA;
  case 0x16:
    return X_COM_STMT_CLOSE;
  case 0x1a:
    return X_COM_STMT_RESET;
  case 0x1b:
    return X_COM_SET_OPTION;
  case 0x1c:
    return X_COM_STMT_FETCH;
  case 0x1d:
    return X_COM_DAEMON;
  case 0x1e:
    return X_COM_BINLOG_DUMP_GTID;
  default:
    return X_COM_END;
  }
}

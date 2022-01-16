# include <stdio.h>
#include <mysql/mysql.h>

int main(int argc, char const *argv[])
{
    
		MYSQL *con = NULL;
		con = mysql_init(con);

		if (con == NULL)
		{
			printf("mysql_init MySQL Error");
			exit(1);
		}
		con = mysql_real_connect(con, NULL, "root", "1234", "jony.db", 9001, NULL, 0);
		if (con == NULL)
		{
			printf("mysql_real_connect MySQL Error %s\n", mysql_error(con));
			exit(1);
		}

        mysql_close(con);

    return 0;
}

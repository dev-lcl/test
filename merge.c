/*练习mysql数据库的查询*/
#include <stdio.h>
#include <string.h>
#include <mysql.h>

/*

gcc -g -c Merge.c -I/usr/include/mysql -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0
gcc -g -o Merge Merge.o -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0 -lssl -lcrypto -lrt -L/usr/local/lib -L/usr/lib64/mysql -lmysqlclient

参数
    ./Merge 1 database
       1 建表 2 不建表
       database： 处理的数据库
*/

int main(int argc, char *argv[])
{
    MYSQL mysql, mysql1, mysql2, mysql3;
    MYSQL_RES *res, *res1;
    MYSQL_ROW row, row1;
    char sCreateTab[102400];
    char sTabName[200];
    char sInsert[102400],query1[1024],sDatabase[100];
    char query[2048];
    char sArr[][20] = {"activityId","age","amount","annualIncome","areaName","birthday","birthday2","carloan","childBirthday","childDate","city","cityId","client","cost","count","credict","credit","createTime","degree","education","educationCnt","email","finanmanageCnt","flyCnt","hadcar","houseloan","income","ip","ipArea","ipCity","ipCityId","ipProvince","ipProvinceId","isBuyInsurance","isInsterest","isNewCar","isNotCard","level","licenceNo","licensePlateNo","mobile","mobileCity","mobileCityId","mobileProvince","mobileProvinceId","mobileType","mobileType2","name","occupation","pattern","payment","paymentPeriod","paymentway","province","provinceId","question1","question2","question3","question4","question5","sex","shoppingCnt","shoufu","shouqi","src","subsidy","sum","taskclickCnt","taskopenCnt","taskregisterCnt","userCityId","userProvinceId","vocation","weiZhi","workingLife","years","yeskid","yunYingShang","CampainId","corpid","sendTaskId","updateTime"};
    int flag, t, ifcreate;
    mysql_init(&mysql);
    mysql_init(&mysql1);
    mysql_init(&mysql2);
    mysql_init(&mysql3);
    char szSource_file[1024];
    char sLine[1024];
    char allrow[102400];
    FILE *pfPlain;
    
    
    if(argc != 4)
    {
    	printf("preace insert like : ./Merge 1 database\n");
    	return 0;
    }
    ifcreate = atoi(argv[1]);
    snprintf(sDatabase, 100, "%s", argv[2]);
    strcpy(szSource_file,argv[3]);
    
    if((pfPlain = fopen(szSource_file, "rb")) == NULL)
    {   
        printf ("==============\nopen file [ %s ] error!\n==============\n", szSource_file);
        return 1;
    }
    int nOffset = 0, k = 0;
    
    while(fgets(sLine, 1024, pfPlain))
	  {
	  	k = snprintf(allrow+nOffset, 102400-nOffset, "%s", sLine);
			nOffset += k; 
	  }
    

    if (ifcreate == 1)
    {
      printf("create table ,and database is <%s>\n", sDatabase);
    }
    else
    {
    	printf("not create table ,and database is <%s>\n", sDatabase);
    }

    	if(!mysql_real_connect(&mysql, "127.0.0.1", "root", 0, "information_schema", 0, NULL, 0)) {
        printf("Failed to connect to Mysql!\n");
        return 0;
    }else {
        printf("Connected to Mysql successfully!\n");
    }
    if(!mysql_real_connect(&mysql1, "127.0.0.1", "root", 0, "information_schema", 0, NULL, 0)) {
        printf("Failed to connect to Mysql!\n");
        return 0;
    }else {
        printf("Connected to Mysql successfully!\n");
    }
    //query = "select CONCAT(COLUMN_NAME,\"   \",min(DATA_TYPE),'(',max(ifnull(CHARACTER_MAXIMUM_LENGTH,4)),')',',') from columns where TABLE_NAME like 't_project_user_%' and TABLE_NAME not like 't_project_user_ext%' group by COLUMN_NAME,DATA_TYPE;";
    char setname[100];
    snprintf(setname, 100, "set names utf8");
    flag = mysql_real_query(&mysql, setname, (unsigned int)strlen(setname));
    
    snprintf(query, 2048, "select CONCAT(\"`\",COLUMN_NAME,\"`\"),CONCAT(\"   \",\"varchar\",'(',max(ifnull(CHARACTER_MAXIMUM_LENGTH,11)),')',\" COMMENT \",\"'\",max(COLUMN_COMMENT),\"'\",',') from columns where TABLE_NAME like 't_project_user_%%' and TABLE_NAME not like 't_project_user_ext%%' group by COLUMN_NAMe");
    /*查询，成功则返回0*/
    flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
    if(flag) {
        printf("Query failed![%s]\n", query);
        return 0;
    }else {
        printf("[%s] made...\n", query);
    }


    /*mysql_store_result讲全部的查询结果读取到客户端*/
    snprintf(sCreateTab, 102400, "CREATE TABLE  If Not Exists t_project_ALL_user (%s", allrow);
    fclose(pfPlain);
    res = mysql_store_result(&mysql);
    //printf("111111111111\n");
    /*mysql_fetch_row检索结果集的下一行*/
    printf("<%s>\n",  allrow);
    //snprintf(allrow, 102400, "%s", tolower(allrow));
    int j;
    for (j = 0; j < strlen(allrow); j++)
    {
       allrow[j] = tolower(allrow[j]);
    }
    
    while(row = mysql_fetch_row(res)) {
        /*mysql_num_fields返回结果集中的字段数目*/
        
        //for (t = 0; t < mysql_num_fields(res); t++) {
      //printf("%s,", row[t]);
     //}
     

          //printf("111111111111");
          char tmp[1024];
          char tmp1[1024];
          char *str;
          snprintf(tmp, 1024, "%s", row[0]);
          snprintf(tmp1, 1024, "%s", row[1]);
          
          //排除80个字段
          int k=0;
          char st[40] ;
          

          	//char st[40] = "`";
          	//strcat(st, sArr[k]);
          	//strcat(st, "`");
          	//printf("<%d><%s><%s>oooooo\n", k, st, tmp);
          	printf("<%s>iiiiiii\n",  tmp);
          	//tolower(allrow);
          	//tolower(tmp);
          	int l;
            for (l = 0; l < strlen(tmp); l++)
            {
               tmp[l] = tolower(tmp[l]);
            }
          	//snprintf(tmp, 1024, "%s", tolower(tmp));
     	      if(strstr(allrow,tmp))
     	      {
     	      	printf("<%s>oooooo\n",  tmp);
     	      	continue;
     	      }

          
          if(strstr(tmp1, "date("))
          {
          	str = strstr(tmp1, "date(");
          	snprintf(str,14,"varchar(60),");
          }
          
          if(strstr(tmp1, "double("))
          {
          	str = strstr(tmp1, "double(");
          	snprintf(str,14,"varchar(60),");
          }
          
          if(strstr(tmp1, "read   varchar(255)"))
          {
          	str = strstr(tmp1, "read   varchar(255)");
          	snprintf(str,30,"`read`   varchar(255),");
          }
          
          if(strstr(tmp1, "decimal("))
          {
          	str = strstr(tmp1, "decimal(");
          	snprintf(str,30,"varchar(60),");
          }
          
          
          
          if(strstr(tmp1, "tinyint("))
          {
          	str = strstr(tmp1, "tinyint(");
          	snprintf(str,30,"int,");
          }
          if(strstr(tmp1, "text("))
          {
          	str = strstr(tmp1, "text(");
          	snprintf(str,30,"text,");
          }
          if(strstr(tmp1, "(255)"))
          {
          	str = strstr(tmp1, "(255)");
          	snprintf(str,30,"(128),");
          }
          
          
          
          if(strstr(tmp1, " int(128)"))
          {
          	str = strstr(tmp1, " int(128)");
          	snprintf(str,30,"varchar(128),");
          }
          if(strstr(tmp1, "varchar(128)"))
          {
          	str = strstr(tmp1, "varchar(128)");
          	snprintf(str,30,"text,");
          }
          
          if(strstr(tmp1, "varchar(65535)"))
          {
          	str = strstr(tmp1, "varchar(65535)");
          	snprintf(str,30,"text,");
          }
          
        	strcat(sCreateTab,tmp);
        	strcat(sCreateTab,"\t");
        	strcat(sCreateTab,tmp1);
          //printf("%s\t", row[0]);

        strcat(sCreateTab,"\n");
        printf("\n");
    }
    sCreateTab[strlen(sCreateTab)-2] =0;
     strcat(sCreateTab,") ENGINE=MyISAM DEFAULT CHARSET=utf8;");
    printf("create<%s>\n", sCreateTab);
        
    if(!mysql_real_connect(&mysql2, "127.0.0.1", "root", 0, sDatabase, 0, NULL, 0)) {
        printf("Failed to connect to Mysql!\n");
        return 0;
    }else {
        printf("Connected to Mysql successfully!\n");
    }
    if(ifcreate == 1)
    {
    	flag = mysql_real_query(&mysql2, sCreateTab, (unsigned int)strlen(sCreateTab));
    	if(flag) {
    	    printf("CreateTab failed!\n");
    	    return 0;
    	}else {
    	    printf("[%s]create success...\n", sCreateTab);
    	}  
    }


    //插入数据
    snprintf(query, 2048, "select distinct TABLE_NAME from columns where TABLE_NAME like 't_project_user_%%' and TABLE_NAME not like 't_project_user_ext%%' and TABLE_SCHEMA = '%s' order by TABLE_NAME",sDatabase);
    flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
    if(flag) {
        printf("Query insert failed![%s]\n", query);
        return 0;
    }else {
        printf("[%s] insert TABLE_NAME made...\n", query);
    }
    //snprintf(sCreateTab, 4096, "insert into t_project_user_ALL (");
    res = mysql_store_result(&mysql);
   // mysql_fetch_row检索结果集的下一行
    printf("1\n");
    while(row = mysql_fetch_row(res)) {
        //查询字段并插入数据
        printf("2\n");
        snprintf(sTabName, 200, "%s", row[0]);
        snprintf(query1, 1024, "select COLUMN_NAME from columns where TABLE_NAME = '%s' and TABLE_NAME not like 't_project_user_ext%%' and TABLE_SCHEMA = '%s' order by TABLE_NAME", sTabName, sDatabase);
         printf("2\n");
        flag = mysql_real_query(&mysql1, query1, (unsigned int)strlen(query1));
         if(flag) {
           printf("Query insert failed!<%s>\n", query1);
           return 0;
    				}else {
           printf("[%s] insert made...\n", query1);
        }
        ///////////////////////////////////
        int k = 0;
        int nOffset =0;
        k = snprintf(sInsert+nOffset, 102400 - nOffset, "insert into campaign_1.t_project_ALL_user (");
        nOffset += k;	
        res1 = mysql_store_result(&mysql1);
        //mysql_fetch_row检索结果集的下一行
        char sTmp[1024];
        snprintf(sTmp,1024," ");
        //printf("3\n");
        while(row1 = mysql_fetch_row(res1)) {
           //mysql_num_fields返回结果集中的字段数目

						strcat(sTmp,"`");
           	strcat(sTmp,row1[0]);
           	strcat(sTmp,"`,");
            //printf("%s\t", sTmp);
           printf("\n");
        }
' ';
        int nCampain, nCorpId;
        nCampain = atoi(sTabName+15);
        printf("4<%s>\n",sTmp);
        char *nDataba;
        nDataba = strstr(sDatabase,"campaign_");
        nDataba = nDataba+9;
        printf("nDataba<%s>", nDataba);
        
        k = snprintf(sInsert+nOffset, 102400 - nOffset, "%sprojectid,corpid", sTmp);
        nOffset += k;

        k = snprintf(sInsert+nOffset, 102400 - nOffset, ") select ");
        nOffset += k;

        k = snprintf(sInsert+nOffset, 102400 - nOffset, "%s%d,%s", sTmp, nCampain, nDataba);
        nOffset += k;

        k = snprintf(sInsert+nOffset, 102400 - nOffset, " from  %s;", sTabName);
        nOffset += k;

        
        flag = mysql_real_query(&mysql2, sInsert, (unsigned int)strlen(sInsert));
        if(flag) {
            printf("[%s]sInsert failed!\n", sInsert);
            return 0;
        }else {
            printf("[%s]sInsert success...\n", sInsert);
        }

        printf("\n");
    }

    mysql_close(&mysql);

    mysql_close(&mysql1);
    printf("congratulations, success!!!");
    return 0;
}











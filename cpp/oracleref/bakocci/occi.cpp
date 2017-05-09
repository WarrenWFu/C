#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <occi.h>

using namespace oracle::occi;
using namespace std;

class  occidml
{
private:
    Environment *env;
    Connection *conn;
    Statement *stmt;
public:
    occidml (string user, string passwd, string db)
    {
        env = Environment::createEnvironment (Environment::DEFAULT);
        conn = env->createConnection (user, passwd, db);
    }

    ~occidml ()
    {
        env->terminateConnection (conn);
        Environment::terminateEnvironment (env);
    }

    //void insertBind (string c1, int c2, string c3, int c4, string c5, string c6)
    void insertBind (int val)
    {
        string sqlStmt = "INSERT INTO T_USI_BIGTXTDATA\
                          (PFWRKDATE, BIGTXTIDEX, BIGTXTTYPE, BIGTXTLEN, BIGTXTCNT, STATE) \
                          VALUES('22220831', :BIGTXTIDEX, 'testtype', 10, 'testtxt', 'TEST')";
        stmt=conn->createStatement (sqlStmt);
        try{
            //stmt->setString (1, c1);
            //stmt->setInt (2, c2);
            //stmt->setString (3, c3);
            //stmt->setInt (4, c4);
            //stmt->setString (5, c5);
            //stmt->setString (6, c6);
            stmt->setInt (1, val);
            stmt->executeUpdate ();
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for insertBind"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        //通过此处阻塞返现，这个类是一次性提交的, 为了测试性能这里增加一个commit
        //string useless;
        //getline(cin, useless);

        conn->commit();
        conn->terminateStatement (stmt);
        //getline(cin, useless);
    }

    /**
     * updating a row
     */
    void updateRow (int val)
    {
        string sqlStmt = 
            "UPDATE T_USI_BIGTXTDATA SET STATE = 'RETE' WHERE BIGTXTIDEX = :1";
        stmt = conn->createStatement (sqlStmt);
        try{
            stmt->setInt (1, val);
            stmt->executeUpdate ();
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for updateRow"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        conn->commit();
        conn->terminateStatement (stmt);
    }


    /**
     * deletion of a row
     */
    void deleteRow (int val)
    {
        string sqlStmt = 
            "DELETE FROM T_USI_BIGTXTDATA WHERE BIGTXTIDEX = :1";
        stmt = conn->createStatement (sqlStmt);
        try{
            stmt->setInt (1, val);
            stmt->executeUpdate ();
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for deleteRow"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        conn->commit();
        conn->terminateStatement (stmt);
    }

    void displayAllRows (int val)
    {
        string sqlStmt = "SELECT BIGTXTIDEX FROM T_USI_BIGTXTDATA WHERE BIGTXTIDEX = :1";
        stmt = conn->createStatement (sqlStmt);
        stmt->setInt (1, val);
        ResultSet *rset = stmt->executeQuery ();
        try{
            while (rset->next ())
            {
                //cout << "结果是[" << rset->getInt (1) << "]" << endl;
            }
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for displayAllRows"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        stmt->closeResultSet (rset);
        conn->terminateStatement (stmt);
    }

    void displayAllRowsWithoutBind (const string &val)
    {
        string sqlStmt = "SELECT BIGTXTIDEX FROM T_USI_BIGTXTDATA WHERE BIGTXTIDEX = ";
        sqlStmt += val;
        stmt = conn->createStatement (sqlStmt);
        ResultSet *rset = stmt->executeQuery ();
        try{
            while (rset->next ())
            {
                //cout << "结果是[" << rset->getInt (1) << "]" << endl;
            }
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for displayAllRows"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        stmt->closeResultSet (rset);
        conn->terminateStatement (stmt);
    }

    /**
     * Inserting a row into elements table.
     * Demonstrating the usage of BFloat and BDouble datatypes
     */
    void insertElement (string elm_name, float mvol=0.0, double awt=0.0)
    {
        BFloat mol_vol;
        BDouble at_wt;

        if (!(mvol))
            mol_vol.isNull = TRUE;
        else
            mol_vol.value = mvol;

        if (!(awt))
            at_wt.isNull = TRUE;
        else
            at_wt.value = awt;

        string sqlStmt = "INSERT INTO elements VALUES (:v1, :v2, :v3)";
        stmt = conn->createStatement (sqlStmt);

        try{
            stmt->setString(1, elm_name);
            stmt->setBFloat(2, mol_vol);
            stmt->setBDouble(3, at_wt);
            stmt->executeUpdate ();
            cout << "insertElement - Success" << endl;
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for insertElement"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }
        conn->terminateStatement (stmt);
    }

    /**
     * displaying rows from element table
     */
    void displayElements ()
    {
        string sqlStmt = 
            "SELECT element_name, molar_volume, atomic_weight FROM elements \
            order by element_name";
        stmt = conn->createStatement (sqlStmt);
        ResultSet *rset = stmt->executeQuery ();
        try{
            cout.precision(7);
            while (rset->next ())
            {
                string elem_name = rset->getString(1);
                BFloat mol_vol = rset->getBFloat(2);
                BDouble at_wt = rset->getBDouble(3);

                cout << "Element Name: " << elem_name << endl;

                if ( mol_vol.isNull )
                    cout << "Molar Volume is NULL" << endl;
                else
                    cout << "Molar Volume: " << mol_vol.value << " cm3 mol-1" << endl;

                if ( at_wt.isNull )
                    cout << "Atomic Weight is NULL" << endl;
                else
                    cout << "Atomic Weight: " << at_wt.value << " g/mole" << endl;
            }
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for displayElements"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        stmt->closeResultSet (rset);
        conn->terminateStatement (stmt);
    }

}; // end of class  occidml


int main (int argc, char *argv[])
{
  string user = "spring_oracle";
  string passwd = "123123";
  string db = "MYDBORACLE";
  try{
      int iLoop = argc > 1? atoi(argv[1]): 1;
      char buffer[10] = {0};

      occidml *demo = new occidml (user, passwd, db);
      for (;iLoop > 0; iLoop--)
      {
          memset(buffer, 0x00, 10);
          sprintf(buffer, "%d", iLoop);
          string sCount(buffer);
          //demo->displayAllRows (iLoop);
          //demo->displayAllRowsWithoutBind (sCount);
          //demo->insertBind ("22220831", iLoop, "testtype", 10, "testtxt", "TEST");
          demo->insertBind (iLoop);
          //demo->updateRow (iLoop);
          //demo->deleteRow (iLoop);
      }
      delete (demo);
  }
  catch (SQLException ex){
    cout << ex.getMessage() << endl;
  }
}

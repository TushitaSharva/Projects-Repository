import java.sql.*;
import java.util.*;

public class ex1
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter number of test cases: ");
        int T = scanner.nextInt();
        scanner.nextLine();

        for(int i = 0; i < T; i++)
        {
            System.out.print("\n\nEnter table name: ");
            String table_name = scanner.nextLine();

            System.out.print("How many rows? ");
            String limit = scanner.nextLine();
            printTable(table_name, limit);
        }

        scanner.close();
    }

    static void printTable(String table_name, String k)
    {
        Connection c = null;
        try
        {
            Class.forName("org.postgresql.Driver");
            c = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb", "tushita", "1234");

            Statement stmt = c.createStatement();
            ResultSet rs;

            rs = stmt.executeQuery("SELECT * FROM " + table_name + " LIMIT " + k);            
            ResultSetMetaData rsmd = rs.getMetaData();

            for(int i = 1; i < rsmd.getColumnCount() + 1; i++)
            {
                System.out.print(String.format("%-50s", rsmd.getColumnName(i)));
            }

            System.out.println();

            while(rs.next())
            {
                for(int i = 1; i < rsmd.getColumnCount() + 1; i++)
                {
                    System.out.print(String.format("%-50s", rs.getString(i)));
                }
                System.out.println();
            }

            rs.close();
            stmt.close();
            c.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.err.println(e.getClass().getName() + ":" + e.getMessage());
            System.exit(0);
        }
    }
}
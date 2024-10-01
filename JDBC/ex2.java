import java.util.*;
import java.sql.*;

public class ex2 {
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);

        System.out.print("\nNumber of test cases: ");
        int T = scanner.nextInt();
        scanner.nextLine();

        for (int i = 0; i < T; i++) 
        {
            System.out.print("\nEnter the course ID: ");
            String course_id = scanner.nextLine();
            prerequisites(course_id);
        }

        scanner.close();
    }

    static void prerequisites(String course_id)
    {
        Connection conn = null;
        try
        {
            Class.forName("org.postgresql.Driver");
            conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb", "tushita", "1234");

            PreparedStatement pStmt = conn.prepareStatement("with recursive rec_prereq(course_id, prereq_id) as (select course_id, prereq_id from prereq union select rec_prereq.course_id, prereq.prereq_id from rec_prereq, prereq where rec_prereq.prereq_id = prereq.course_id) select rec_prereq.course_id, prereq_id, course.title from rec_prereq, course WHERE rec_prereq.prereq_id = course.course_id and rec_prereq.course_id = ?;");
            pStmt.setString(1, course_id);
            ResultSet rs = pStmt.executeQuery();

            while (rs.next()) {
                System.out.println(rs.getString(2) + "\t" + rs.getString(3));
            }

            rs.close();
            conn.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.err.println(e.getClass().getName() + ":" + e.getMessage());
            System.exit(0);
        }
    }
}
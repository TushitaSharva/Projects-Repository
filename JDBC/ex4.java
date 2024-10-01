import java.util.*;
import java.sql.*;

public class ex4 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("\nEnter number of test cases: ");
        int testCases = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < testCases; i++) {
            System.out.print("\nRoll Number of the student: ");
            String roll_number = scanner.nextLine();
            findingCGPA(roll_number);
        }
        scanner.close();
    }

    static void findingCGPA(String n) {
        Connection c = null;
        try {
            Boolean isEmpty = true;
            Class.forName("org.postgresql.Driver");
            c = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb", "tushita", "1234");

            PreparedStatement pStmt = c.prepareStatement("SELECT sum(takes.grade_point*course.credits)/sum(course.credits) FROM course, takes WHERE course.course_id = takes.course_id and takes.id = ?");
            pStmt.setString(1, n);
            ResultSet rs = pStmt.executeQuery();

            while (rs.next() == true) {

                if(rs.getString(1) != null)
                {
                    isEmpty = false;
                    System.out.println("CGPA is " + rs.getString(1) + "\n");
                }
            }
            
            if(isEmpty == true)
            {
                System.out.println("No such existing ID");
            }

            rs.close();
            c.close();
        }

        catch (Exception e) {
            e.printStackTrace();
            System.err.println(e.getClass().getName() + ":" + e.getMessage());
            System.exit(0);
        }
    }
}

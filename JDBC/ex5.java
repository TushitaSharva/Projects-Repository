import java.util.*;
import java.sql.*;

public class ex5 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Number of test cases: ");
        int testCases = scanner.nextInt();
        scanner.nextLine();

        for (int i = 0; i < testCases; i++)
        {
            System.out.println("\nWhich Information do you want?");
            System.out.println("(1) Top-k students with highest CGPA");
            System.out.println("(2) Top-k students with highest CGPA in a given department");
            System.out.println("(3) Top-k students with highest CGPA in a given course");
            System.out.print("Your choice: ");
            int choice = scanner.nextInt();
            scanner.nextLine();

            int limit;
            switch (choice) {
                case 1:
                    System.out.print("Number of students: ");
                    limit = scanner.nextInt();
                    overallToppers(limit);
                    break;
                case 2:
                    System.out.print("Number of students: ");
                    limit = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Department name: ");
                    String dept = scanner.nextLine();
                    deptWiseToppers(limit, dept);
                    break;
                case 3:
                    System.out.print("Number of students: ");
                    limit = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Course ID: ");
                    String courseID = scanner.nextLine();
                    courseWiseToppers(limit, courseID);
                    break;
                default:
                    break;
            }
        }

        scanner.close();
    }

    static void overallToppers(int limit)
    {
        Connection c = null;
        try {
            Class.forName("org.postgresql.Driver");
            c = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb", "tushita", "1234");

            PreparedStatement pStmt = c.prepareStatement("SELECT student.id, student.name, student.dept_name, sum(takes.grade_point*course.credits)/sum(course.credits) as cgpa, rank() over (order by sum(takes.grade_point*course.credits)/sum(course.credits) desc) as s_rank FROM student, takes, course WHERE course.course_id = takes.course_id and student.id = takes.id GROUP BY student.id LIMIT ?;");
            pStmt.setInt(1, limit);
            ResultSet rs = pStmt.executeQuery();

            while (rs.next() == true) {
                System.out.println("Rank " + rs.getString("s_rank")+ ":\t" + rs.getString(1) + "\t" + String.format("%-20s", rs.getString(2))+ "\t" + String.format("%-20s", rs.getString(3)) + "\t" + rs.getString(4));
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

    static void deptWiseToppers(int limit, String dept_name)
    {
        Connection c = null;
        try {
            Class.forName("org.postgresql.Driver");
            c = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb", "tushita", "1234");

            PreparedStatement pStmt = c.prepareStatement("SELECT student.id, student.name, student.dept_name, sum(takes.grade_point*course.credits)/sum(course.credits) as cgpa, rank() over (order by sum(takes.grade_point*course.credits)/sum(course.credits) desc) as s_rank FROM student, takes, course WHERE course.course_id = takes.course_id and student.id = takes.id and student.dept_name = ? GROUP BY student.id ORDER BY sum(takes.grade_point*course.credits)/sum(course.credits) desc LIMIT ?");
            pStmt.setString(1, dept_name);
            pStmt.setInt(2, limit);
            ResultSet rs = pStmt.executeQuery();

            while (rs.next() == true) {
                System.out.println("Rank " + rs.getString("s_rank") + ":\t" + rs.getString(1) + "\t" + String.format("%-20s", rs.getString(2))+ "\t" + rs.getString(4) +"\t" + rs.getString(3));
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

    static void courseWiseToppers(int limit, String course_id)
    {
        Connection c = null;
        try {
            Class.forName("org.postgresql.Driver");
            c = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb", "tushita", "1234");

            PreparedStatement pStmt = c.prepareStatement("WITH cgpa_list AS(SELECT takes.id as s_id, SUM(course.credits*takes.grade_point)/SUM(course.credits) AS cgpa FROM takes, course WHERE takes.course_id = course.course_id GROUP BY takes.id) SELECT takes.id, student.name, takes.course_id, cgpa, rank() over (order by cgpa desc) as s_rank FROM takes, cgpa_list, student WHERE takes.id = cgpa_list.s_id and takes.id = student.id and takes.course_id = ? LIMIT ?;");
            pStmt.setString(1, course_id);
            pStmt.setInt(2, limit);
            ResultSet rs = pStmt.executeQuery();

            while (rs.next() == true) {
                System.out.println("Rank " + rs.getString("s_rank") + ":\t" + rs.getString(3) + "\t" + rs.getString(1) + "\t" + String.format("%-20s", rs.getString(2)) + "\t" + rs.getString(4));
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
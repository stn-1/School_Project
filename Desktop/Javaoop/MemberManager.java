import java.awt.*;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.*;

// Lớp cha
class Member {
    protected String code;
    protected String fullName;
    protected int birthYear;

    public Member(String code, String fullName, int birthYear) {
        this.code = code;
        this.fullName = fullName;
        this.birthYear = birthYear;
    }

    public String getCode() {
        return code;
    }

    public String getFullName() {
        return fullName;
    }

    public int getBirthYear() {
        return birthYear;
    }

    public int getAge() {
        return java.time.Year.now().getValue() - birthYear;
    }

    public String toString() {
        return code + " - " + fullName + " (" + getAge() + ")";
    }
}

// Học viên
// Học viên
class Learner extends Member {
    private String course;
    private double grade;

    public Learner(String code, String fullName, int birthYear, String course, double grade) {
        super(code, fullName, birthYear);
        this.course = course;
        this.grade = grade;
    }

    public String getCourse() {
        return course;
    }

    public double getGrade() {
        return grade;
    }
    public String toString() {
        return "[HV] " + super.toString() + " - " + course + " - Grade: " + grade;
    }
}

// Giảng viên
class Instructor extends Member {
    private String faculty;
    private double hourlyRate;

    public Instructor(String code, String fullName, int birthYear, String faculty, double hourlyRate) {
        super(code, fullName, birthYear);
        this.faculty = faculty;
        this.hourlyRate = hourlyRate;
    }

    public String getFaculty() {
        return faculty;
    }

    public double getHourlyRate() {
        return hourlyRate;
    }

    public String toString() {
        return "[GV] " + super.toString() + " - " + faculty + " - Rate: " + hourlyRate;
    }
}

// Giao diện chính
public class MemberManager extends JFrame {
    private JTextField txtCode, txtName, txtBirthYear, txtExtra1, txtExtra2;
    private JComboBox<String> typeCombo;
    private DefaultListModel<Member> listModel;
    private JList<Member> memberList;

    public MemberManager() {
        setTitle("Quản lý thành viên");
        setSize(500, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Input Panel
        JPanel inputPanel = new JPanel(new GridLayout(6, 2, 5, 5));
        inputPanel.add(new JLabel("Code:"));
        txtCode = new JTextField();
        inputPanel.add(txtCode);

        inputPanel.add(new JLabel("Full name:"));
        txtName = new JTextField();
        inputPanel.add(txtName);

        inputPanel.add(new JLabel("Birth year:"));
        txtBirthYear = new JTextField();
        inputPanel.add(txtBirthYear);

        inputPanel.add(new JLabel("Membership Type:"));
        typeCombo = new JComboBox<>(new String[]{"Student", "Instructor"});
        inputPanel.add(typeCombo);

        inputPanel.add(new JLabel("Course / Department:"));
        txtExtra1 = new JTextField();
        inputPanel.add(txtExtra1);

        inputPanel.add(new JLabel("Points / Hourly Wage:"));
        txtExtra2 = new JTextField();
        inputPanel.add(txtExtra2);

        // List + Scroll
        listModel = new DefaultListModel<>();
        memberList = new JList<>(listModel);
        JScrollPane scrollPane = new JScrollPane(memberList);

        // Button Panel
        JPanel btnPanel = new JPanel();
        JButton btnThem = new JButton("Add");
        JButton btnXoa = new JButton("Delete");
        JButton btnSua = new JButton("Fix");
        JButton btnTB = new JButton("Average");
        JButton btnfind=new JButton("Find");
        JButton btnExport=new JButton("Export");
        btnPanel.add(btnThem);
        btnPanel.add(btnSua);
        btnPanel.add(btnXoa);
        btnPanel.add(btnTB);
        btnPanel.add(btnfind);
        btnPanel.add(btnExport);

        // Add panels to layout
        setLayout(new BorderLayout());
        add(inputPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
        add(btnPanel, BorderLayout.SOUTH);

        // Event: chọn thành viên -> hiển thị lên ô nhập
        memberList.addListSelectionListener(e -> {
    if (!e.getValueIsAdjusting()) {
        int index = memberList.getSelectedIndex();
        if (index != -1) {
            Member m = listModel.get(index);
            txtCode.setText(m.getCode());
            txtName.setText(m.getFullName());
            txtBirthYear.setText(String.valueOf(m.getBirthYear()));
            if (m instanceof Learner) {
                Learner l = (Learner) m;
                typeCombo.setSelectedIndex(0);
                txtExtra1.setText(l.getCourse());
                txtExtra2.setText(String.valueOf(l.getGrade()));
            } else if (m instanceof Instructor) {
                Instructor i = (Instructor) m;
                typeCombo.setSelectedIndex(1);
                txtExtra1.setText(i.getFaculty());
                txtExtra2.setText(String.valueOf(i.getHourlyRate()));
            }
        }
    }
});


        // Thêm
        btnThem.addActionListener(e -> {
            String code = txtCode.getText().trim();
            String name = txtName.getText().trim();
            int year = Integer.parseInt(txtBirthYear.getText().trim());
            String ex1 = txtExtra1.getText().trim();
            double ex2 = Double.parseDouble(txtExtra2.getText().trim());

            Member m;
            if (typeCombo.getSelectedIndex() == 0) {
                m = new Learner(code, name, year, ex1, ex2);
            } else {
                m = new Instructor(code, name, year, ex1, ex2);
            }
            listModel.addElement(m);
            clearFields();
        });

        // Xóa
        btnXoa.addActionListener(e -> {
            int index = memberList.getSelectedIndex();
            if (index != -1) {
                listModel.remove(index);
                clearFields();
            }
        });

        // Sửa
        btnSua.addActionListener(e -> {
            int index = memberList.getSelectedIndex();
            if (index != -1) {
                String code = txtCode.getText().trim();
                String name = txtName.getText().trim();
                int year = Integer.parseInt(txtBirthYear.getText().trim());
                String ex1 = txtExtra1.getText().trim();
                double ex2 = Double.parseDouble(txtExtra2.getText().trim());

                Member m;
                if (typeCombo.getSelectedIndex() == 0) {
                    m = new Learner(code, name, year, ex1, ex2);
                } else {
                    m = new Instructor(code, name, year, ex1, ex2);
                }
                listModel.set(index, m);
                clearFields();
            }
        });
        //tìm kiếm
        btnfind.addActionListener(e -> {
    String findCode = JOptionPane.showInputDialog(this, "Enter your Code:");

    if (findCode != null && !findCode.trim().isEmpty()) {
        boolean found = false;

        for (int i = 0; i < listModel.size(); i++) {
            Member m = listModel.get(i);
            if (m.getCode().equalsIgnoreCase(findCode.trim())) {
                memberList.setSelectedIndex(i); // chọn thành viên
                JOptionPane.showMessageDialog(this, "Found:\n" + m.toString());
                found = true;
                break;
            }
        }

        if (!found) {
            JOptionPane.showMessageDialog(this, "Code not found: " + findCode);
        }

    } else {
        JOptionPane.showMessageDialog(this, "You did not enter your code.");
    }
});


        // Tuổi trung bình
        btnTB.addActionListener(e -> {
            if (listModel.isEmpty()) {
                JOptionPane.showMessageDialog(this, "There are no members.");
                return;
            }
            int sum = 0;
            for (int i = 0; i < listModel.size(); i++) {
                sum += listModel.get(i).getAge();
            }
            double avg = (double) sum / listModel.size();
            JOptionPane.showMessageDialog(this,"Average age: " + String.format("%.2f", avg));
        });
        btnExport.addActionListener(e -> {
            try {
                BufferedWriter bwLearner = new BufferedWriter(new FileWriter("learners.txt"));
                BufferedWriter bwInstructor = new BufferedWriter(new FileWriter("instructors.txt"));

                for (int i = 0; i < listModel.size(); i++) {
                    Member m = listModel.get(i);
                    if (m instanceof Learner) {
                        Learner l = (Learner) m;
                        bwLearner.write(l.getCode() + "," + l.getFullName() + "," + l.getBirthYear()
                                        + "," + l.getCourse() + "," + l.getGrade());
                        bwLearner.newLine();
                    } else if (m instanceof Instructor) {
                        Instructor ins = (Instructor) m;
                        bwInstructor.write(ins.getCode() + "," + ins.getFullName() + "," + ins.getBirthYear()
                                        + "," + ins.getFaculty() + "," + ins.getHourlyRate());
                        bwInstructor.newLine();
                    }
                }

                bwLearner.close();
                bwInstructor.close();

                JOptionPane.showMessageDialog(this, "List saved to file!");
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(this, "Lỗi khi ghi file: " + ex.getMessage());
            }
});

        setVisible(true);
    }

    private void clearFields() {
        txtCode.setText("");
        txtName.setText("");
        txtBirthYear.setText("");
        txtExtra1.setText("");
        txtExtra2.setText("");
        memberList.clearSelection();
    }

    public static void main(String[] args) {
        new MemberManager();
    }
}

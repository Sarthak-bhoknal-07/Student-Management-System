import java.awt.*;
import java.io.*;
import javax.swing.*;

public class StudentGradeCalculator {
    private static JFrame frame;
    private static JPanel panel;
    private static JTextField nameField, seatNoField, subjectCountField;
    private static JButton nextButton, calculateButton, showHistoryButton, backButton;
    private static JTextField[] subjectFields;
    private static JTextField[] subjectNameFields;
    private static final String FILE_NAME = "grade_history.txt";

    public static void main(String[] args) {
        createInitialWindow();
    }

    private static void createInitialWindow() {
        frame = new JFrame("Student Grade Calculator");
        frame.setSize(500, 650);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        panel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10);

        // Student Name
        JLabel nameLabel = new JLabel("Enter Student Name:");
        gbc.gridx = 0; gbc.gridy = 0;
        gbc.anchor = GridBagConstraints.WEST;
        panel.add(nameLabel, gbc);

        nameField = new JTextField(20);
        gbc.gridx = 1;
        panel.add(nameField, gbc);

        // Seat Number
        JLabel seatLabel = new JLabel("Enter Seat Number:");
        gbc.gridx = 0; gbc.gridy = 1;
        panel.add(seatLabel, gbc);

        seatNoField = new JTextField(20);
        gbc.gridx = 1;
        panel.add(seatNoField, gbc);

        // Number of Subjects
        JLabel subjectLabel = new JLabel("How many subjects?");
        gbc.gridx = 0; gbc.gridy = 2;
        panel.add(subjectLabel, gbc);

        subjectCountField = new JTextField(5);
        gbc.gridx = 1;
        panel.add(subjectCountField, gbc);

        // Buttons
        nextButton = new JButton("Next");
        gbc.gridx = 1; gbc.gridy = 3;
        gbc.anchor = GridBagConstraints.EAST;
        panel.add(nextButton, gbc);

        showHistoryButton = new JButton("Show History");
        gbc.gridx = 0;
        panel.add(showHistoryButton, gbc);

        nextButton.addActionListener(e -> showSubjectFields());
        showHistoryButton.addActionListener(e -> showHistory());

        frame.setContentPane(panel);
        frame.setVisible(true);
    }

    private static void showSubjectFields() {
        try {
            int count = Integer.parseInt(subjectCountField.getText());
            if (count <= 0) throw new NumberFormatException();

            panel = new JPanel(new GridBagLayout());
            GridBagConstraints gbc = new GridBagConstraints();
            gbc.insets = new Insets(10, 10, 10, 10);

            JLabel marksLabel = new JLabel("Enter Subject Names and Marks:");
            gbc.gridx = 0; gbc.gridy = 0; gbc.gridwidth = 2;
            panel.add(marksLabel, gbc);

            subjectFields = new JTextField[count];
            subjectNameFields = new JTextField[count];

            for (int i = 0; i < count; i++) {
                gbc.gridwidth = 1;
                gbc.gridy = i + 1;

                gbc.gridx = 0;
                subjectNameFields[i] = new JTextField(10);
                panel.add(subjectNameFields[i], gbc);

                gbc.gridx = 1;
                subjectFields[i] = new JTextField(10);
                panel.add(subjectFields[i], gbc);
            }

            calculateButton = new JButton("Calculate");
            gbc.gridy = count + 1;
            gbc.gridx = 1;
            panel.add(calculateButton, gbc);
            calculateButton.addActionListener(e -> calculateResult(count));

            backButton = new JButton("Back");
            gbc.gridx = 0;
            panel.add(backButton, gbc);
            backButton.addActionListener(e -> createInitialWindow());

            frame.setContentPane(panel);
            frame.revalidate();
            frame.repaint();

        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(frame, "Please enter a valid number of subjects.");
        }
    }

    private static void calculateResult(int count) {
        try {
            int total = 0;
            StringBuilder subjects = new StringBuilder();

            for (int i = 0; i < count; i++) {
                int mark = Integer.parseInt(subjectFields[i].getText());
                String subjectName = subjectNameFields[i].getText();
                subjects.append(subjectName).append(": ").append(mark).append("\n");
                total += mark;
            }

            double percentage = total / (double) count;
            char grade;

            if (percentage >= 90) grade = 'A';
            else if (percentage >= 75) grade = 'B';
            else if (percentage >= 60) grade = 'C';
            else if (percentage >= 40) grade = 'D';
            else grade = 'F';

            String name = nameField.getText();
            String seatNo = seatNoField.getText();

            String result = "Name: " + name +
                            "\nSeat No: " + seatNo +
                            "\n" + subjects +
                            "Total: " + total +
                            "\nPercentage: " + percentage + "%" +
                            "\nGrade: " + grade;

            JOptionPane.showMessageDialog(frame, result, "Result", JOptionPane.INFORMATION_MESSAGE);
            saveToFile(result);

        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(frame, "Please enter valid numeric marks.");
        }
    }

    private static void saveToFile(String data) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, true))) {
            writer.write(data);
            writer.write("\n-----------------------------\n");
        } catch (IOException e) {
            JOptionPane.showMessageDialog(frame, "Error saving data to file.");
        }
    }

    private static void showHistory() {
        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            StringBuilder history = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                history.append(line).append("\n");
            }
            JTextArea textArea = new JTextArea(history.toString());
            textArea.setEditable(false);
            JScrollPane scrollPane = new JScrollPane(textArea);
            scrollPane.setPreferredSize(new Dimension(450, 300));
            JOptionPane.showMessageDialog(frame, scrollPane, "History", JOptionPane.INFORMATION_MESSAGE);
        } catch (IOException e) {
            JOptionPane.showMessageDialog(frame, "No history available.");
        }
    }
}
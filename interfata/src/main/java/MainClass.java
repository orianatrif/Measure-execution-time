import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;

import javax.swing.*;

public class MainClass extends JFrame {

    public MainClass(String title) {
        super(title);

        CategoryDataset dataset = createDataset();
        JFreeChart chart = ChartFactory.createBarChart(
                "Sample Bar Chart",
                "Categorie",
                "Value",
                dataset
        );

        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new java.awt.Dimension(560, 370));
        setContentPane(chartPanel);
    }

    private CategoryDataset createDataset() {
        DefaultCategoryDataset dataset = new DefaultCategoryDataset();

        dataset.addValue(1.0, "Series1", "Category1");
        dataset.addValue(4.0, "Series1", "Category2");
        dataset.addValue(3.0, "Series1", "Category3");
        dataset.addValue(50.0, "Series1", "Category4");

        return dataset;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MainClass example = new MainClass("JFreeChart Example");
            example.setSize(800, 600);
            example.setLocationRelativeTo(null);
            example.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            example.setVisible(true);
        });
    }
}

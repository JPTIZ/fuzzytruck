import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.plot.JFuzzyChart;

public class Charter {
    public static void main(String... args) {
        if (args.length < 2) {
            System.out.println("Usage: <thisapp> <FCL filename> <function block>");
            System.exit(1);
        }

        var fileName = args[0];

        var fis = FIS.load(fileName, true);
        if (fis == null) {
            System.err.println("Can't load file: '" + fileName + "'");
            return;
        }

        var fb = fis.getFunctionBlock(args[1]);

        JFuzzyChart.get().chart(fb);
    }
}

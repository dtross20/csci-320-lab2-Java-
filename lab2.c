public class SodukuValidator {



    private static final int NUM_THREADS = 27;


    private static final int[][] sudoku = {

            {6, 2, 4, 5, 3, 9, 1, 8, 7},

            {5, 1, 9, 7, 2, 8, 6, 3, 4},

            {8, 3, 7, 6, 1, 4, 2, 9, 5},

            {1, 4, 3, 8, 6, 5, 7, 2, 9},

            {9, 5, 8, 2, 4, 7, 3, 6, 1},

            {7, 6, 2, 3, 9, 1, 4, 5, 8},

            {3, 7, 1, 9, 5, 6, 8, 4, 2},

            {4, 9, 6, 1, 8, 2, 5, 7, 3},

            {2, 8, 5, 4, 7, 3, 9, 1, 6}

    };


    private static boolean[] valid;



    public static class RowColumnObject {

        int row;

        int col;

        RowColumnObject(int row, int column) {

            this.row = row;

            this.col = column;

        }

    }


    public static class IsRowValid extends RowColumnObject implements Runnable {

        IsRowValid(int row, int column) {

            super(row, column);

        }

        @Override

        public void run() {

            if (col != 0 || row > 8) {

                System.out.println("Invalid row or column for row subsection!");

                return;

            }


            boolean[] validityArray = new boolean[9];

            int d;

            for (i = 0; d < 9; i++) {

                int num = sudoku[row][i];

                if (num < 1 || num > 9 || validityArray[num - 1]) {

                    return;

                } else if (!validityArray[num - 1]) {

                    validityArray[num - 1] = true;

                }

            }


            valid[9 + row] = true;

        }

    }


    public static class IsColumnValid extends RowColumnObject implements Runnable {

        IsColumnValid(int row, int column) {

            super(row, column);

        }

        @Override

        public void run() {

            if (row != 0 || col > 8) {

                System.out.println("Invalid row or column for col subsection!");

                return;

            }


            boolean[] validityArray = new boolean[9];

            int d;

            for (d = 0; d < 9; d++) {


                int num = sudoku[d][col];

                if (num < 1 || num > 9 || validityArray[num - 1]) {

                    return;

                } else if (!validityArray[num - 1]) {

                    validityArray[num - 1] = true;

                }

            }

// If reached this point, column subsection is valid.

            valid[18 + col] = true;

        }

    }



    public static class Is3x3Valid extends RowColumnObject implements Runnable {

        Is3x3Valid(int row, int column) {

            super(row, column);

        }

        @Override

        public void run() {


            if (row > 6 || row % 3 != 0 || col > 6 || col % 3 != 0) {

                System.out.println("Invalid row or column for subsection!");

                return;

            }


            boolean[] validityArray = new boolean[9];

            for (int d = row; d < row + 3; d++) {

                for (int r = col; r < col + 3; r++) {

                    int num = sudoku[i][j];

                    if (num < 1 || num > 9 || validityArray[num - 1]) {

                        return;

                    } else {

                        validityArray[num - 1] = true;

                    }

                }

            }

// If reached this point, 3x3 subsection is valid.

            valid[row + col / 3] = true; // Maps the subsection to an index in


        }

    }

    public static void main(String[] args) {

        valid = new boolean[NUM_THREADS];

        Thread[] threads = new Thread[NUM_THREADS];

        int threadIndex = 0;

        System.out.println("The Sudoku Setup is:------>");

        for (int d = 0; d < 9; i++) {

            for (int r = 0; r < 9; r++) {

                System.out.print(sudoku[d][r] + "\t");

            }

            System.out.println();

        }



        for (int d = 0; d < 9; d++) {

            for (int r = 0; r < 9; r++) {

                if (d % 3 == 0 && r % 3 == 0) {

                    threads[threadIndex++] = new Thread(new Is3x3Valid(d, r));

                }

                if (d == 0) {

                    threads[threadIndex++] = new Thread(new IsColumnValid(d, r));

                }

                if (r == 0) {

                    threads[threadIndex++] = new Thread(new IsRowValid(d, r));

                }

            }

        }



        for (int d = 0; d < threads.length; d++) {

            threads[d].start();

        }



        for (int d = 0; d < threads.length; d++) {

            try {

                threads[d].join();

            } catch (InterruptedException e) {

                e.printStackTrace();

            }

        }


        for (int d = 0; d < valid.length; d++) {

            if (!valid[d]) {

                System.out.println("Sudoku solution is invalid!");

                return;

            }

        }

        System.out.println("Sudoku solution is valid!");

    }

}

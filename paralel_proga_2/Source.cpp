#include<iostream>
#include<fstream>
#include<random>
#include<chrono>
#include<time.h>
#include<omp.h>

using namespace std;
using namespace std::chrono;

class MULTI_MATRIX {
private:
    int size;
    int** matrix1;
    int** matrix2;
    int** result_matrix;
    string filename_matrix1 = "matrix1.txt";
    string filename_matrix2 = "matrix2.txt";
    string filename_matrix_res = "result_matrix.txt";

    int** create_matrix() {
        int** matrix = new int* [size];
        for (int i = 0; i < size; ++i)
            matrix[i] = new int[size];
        return matrix;
    }

    void random_matrix_file(int*** matrix, const string& filename) {
        srand(time(NULL));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                (*matrix)[i][j] = rand() % 100;
            }
        }
        ofstream file(filename);
        file << size << endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file << (*matrix)[i][j] << " ";
            }
            file << endl;
        }
        file.close();
    }

    void write_file(int** matrix, const string& filename) {
        ofstream file(filename);
        file << size << endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file << matrix[i][j] << " ";
            }
            file << endl;
        }
        file.close();
    }

public:
    MULTI_MATRIX(int N) {
        this->size = N;
        matrix1 = create_matrix();
        matrix2 = create_matrix();
        result_matrix = create_matrix();
    }

    void generate_matrix() {
        random_matrix_file(&matrix1, filename_matrix1);
        random_matrix_file(&matrix2, filename_matrix2);
    }

    void multiply() {
        #pragma omp parallel for 
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result_matrix[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    result_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        write_file(result_matrix, filename_matrix_res);
    }

    void clean(int*** matrix) {
        for (int i = 0; i < size; ++i) {
            delete[](*matrix)[i];
        }
        delete[](*matrix);
    }

    ~MULTI_MATRIX() {
        clean(&matrix1);
        clean(&matrix2);
        clean(&result_matrix);
    }
};

void write_time_file(long long computation_time, const string& filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        exit(1);
    }

    file << computation_time << endl;

    file.close();
}

void write_task_file(int size, long long task_size, const string& filename) {
    ofstream file(filename, ios::app);
    file << size << endl << task_size << endl;
    file.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    int size_0 = 100;
    int num_threads = 8;
    string file_stat = "stats_8.txt";
    cout << "Число ядер: " << omp_get_num_procs() << endl;
     
    while (size_0 <= 1000) {
        long long task_size = static_cast<long long>(size_0) * static_cast<long long>(size_0) * static_cast<long long>(size_0);
        write_task_file(size_0, task_size, file_stat);
        cout << "Размер матриц " << size_0 << "x" << size_0 << endl << "Объем задачи: " << task_size << endl;

        for(size_t i = 0; i < 10; ++i) {
            MULTI_MATRIX matrix(size_0);

            matrix.generate_matrix();

            omp_set_num_threads(num_threads);

            auto start_compute = high_resolution_clock::now();
            matrix.multiply();
            auto stop_compute = high_resolution_clock::now();;

            auto duration_computation = duration_cast<milliseconds>(stop_compute - start_compute);

            cout << "Время умножения матриц: " << duration_computation.count() << " мс" << endl;
            write_time_file(duration_computation.count(), file_stat);
        }
        size_0 += 100;
    }
    return 0;
}
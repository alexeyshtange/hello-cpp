
pipeline {
    agent {
        label 'cpp'
    }

    options {
        timestamps()
    }

    stages {
        stage('Configure') {
            steps {
                sh 'cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release'
            }
        }

        stage('Build') {
            steps {
                sh 'cmake --build build --parallel'
            }
        }

        stage('Test') {
            steps {
                sh 'ctest --test-dir build --output-on-failure'
            }
        }
    }

    post {
        success {
            echo 'Build and tests completed successfully!'
        }
        failure {
            echo 'Build or tests failed. Check the console output.'
        }
    }
}

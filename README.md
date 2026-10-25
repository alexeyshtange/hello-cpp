1. Launch Docker Desktop
Ensure that Docker is running:
docker --version


2. Build the images
Copy the `hello-cpp` project and the Dockerfiles to `C:\jenkins-lab`. The directory should contain `Dockerfile` and `Dockerfile.agent`.
cd C:\jenkins-lab

docker build -t cpp-build:1.0 .
docker build -t cpp-agent:1.0 -f Dockerfile.agent .


3. Create a network and launch Jenkins
docker network create jenkins-net

docker volume create jenkins_home

docker run -d --name jenkins --restart unless-stopped `
-p 127.0.0.1:8080:8080 `
-v jenkins_home:/var/jenkins_home `
jenkins/jenkins:lts-jdk21

docker network connect jenkins-net jenkins


Open `http://localhost:8080` and set up Jenkins from scratch: install plugins, create an account, and configure credentials for GitHub.
4. Create an agent in Jenkins
Go to **Manage Jenkins → Nodes** and create a new node:
- Name: `cpp-agent`
- Remote root: `/home/jenkins/agent`
- Labels: `cpp`
- Launch method: "Launch agent by connecting it to the controller"
- Enable WebSocket, if the option is available.
5. Start the agent container
Retrieve the connection command from the Jenkins node settings and use the new secret — the old one from a different machine will not work. Example:
docker run -d --name cpp-agent --restart unless-stopped `
--network jenkins-net `
cpp-agent:1.0 `
-url http://jenkins:8080 `
-secret "NEW_SECRET" `
-name cpp-agent `
-webSocket `
-workDir /home/jenkins/agent


6. Run the project
In Jenkins, create a Pipeline job named `cpp-pipeline`, specify the GitHub repository and the path to the `Jenkinsfile`. Then, click "Build Now."

Important: The `cpp-build:1.0` image is not required for this specific Pipeline, as the compiler and CMake are already installed in `cpp-agent:1.0`. You only need to build both images if you wish to keep both environment variants available.

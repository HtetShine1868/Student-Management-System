
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <iomanip>
#include <limits>
#include <sstream>

class QuestionnaireLogic
{
public:
    QuestionnaireLogic();
    std::string GetCurrentQuestion() const;
    void AnswerYes();
    void AnswerNo();
    bool IsFinished() const;
    const std::vector<bool>& GetAnswers() const;

private:
    std::vector<std::string> questions;
    int currentQuestion;
    std::vector<bool> answers;
    void NextQuestion();
};

class DegreeRecommendation
{
public:
    DegreeRecommendation(const std::vector<bool>& answers);
    std::string GetRecommendedDegree() const;
    std::pair<double, double> GetDegreePercentages() const;

private:
    std::string recommendedDegree;
    int csScore;
    int ctScore;
};

class MajorSelectionLogic
{
public:
    MajorSelectionLogic(const std::string& degree);
    const std::vector<std::string>& GetMajors() const;
    std::pair<std::string, std::string> GetMajorQuestions(const std::string& major) const;

private:
    std::string degree;
    std::vector<std::string> majors;
    std::map<std::string, std::pair<std::string, std::string>> majorQuestions;
};

std::map<std::string, std::vector<std::string>> getBachelorDegrees() {
    return {
        {"Computer Science", {
            "Bachelor of Software Engineering in Computer Science",
            "Bachelor of Business Information Systems in Computer Science",
            "Bachelor of Knowledge Engineering in Computer Science",
            "Bachelor of High Performance Computing in Computer Science"
        }},
        {"Computer Technology", {
            "Bachelor of Embedded Systems in Computer Technology",
            "Bachelor of Communication and Networking in Computer Technology",
            "Bachelor of Cyber Security in Computer Technology"
        }}
    };
}

void displayBachelorDegrees() {
    auto degrees = getBachelorDegrees();
    for (const auto& field : degrees) {
        std::cout << field.first << " degrees:\n";
        for (const auto& degree : field.second) {
            std::cout << "- " << degree << "\n";
        }
        std::cout << "\n";
    }
}

QuestionnaireLogic::QuestionnaireLogic() : currentQuestion(0)
{
    questions = {
        "Are you interested in learning multiple programming languages like Python, Java, or C++?",
        "Do you want to design and implement algorithms to solve specific problems?",
        "Are you inclined towards understanding the theory behind how computers process information?",
        "Would you enjoy working on software that improves the performance of computer systems?",
        "Are you more interested in developing apps or software rather than maintaining network systems?",
        "Do you want to explore the mathematical foundations of computing, such as discrete mathematics and logic?",
        "Are you interested in cybersecurity from a software development perspective rather than a network management one?",
        "Do you want to research and innovate in fields like quantum computing or blockchain technology?",
        "Are you less interested in tasks like configuring servers or managing databases?",
        "Would you prefer to write code for developing new technologies rather than setting up existing ones?"
    };
}

std::string QuestionnaireLogic::GetCurrentQuestion() const
{
    return questions[currentQuestion];
}

void QuestionnaireLogic::AnswerYes()
{
    answers.push_back(true);
    NextQuestion();
}

void QuestionnaireLogic::AnswerNo()
{
    answers.push_back(false);
    NextQuestion();
}

void QuestionnaireLogic::NextQuestion()
{
    currentQuestion++;
}

bool QuestionnaireLogic::IsFinished() const
{
    return currentQuestion >= questions.size();
}

const std::vector<bool>& QuestionnaireLogic::GetAnswers() const
{
    return answers;
}


DegreeRecommendation::DegreeRecommendation(const std::vector<bool>& answers)
    : csScore(0), ctScore(0)
{
    if (answers[0]) csScore += 2;
    if (answers[1]) csScore += 2;
    if (answers[2]) ctScore += 2;
    if (answers[3]) csScore += 2;
    if (answers[4]) csScore += 1;
    if (answers[5]) { csScore += 1; ctScore += 1; }
    if (answers[6]) ctScore += 2;
    if (answers[7]) ctScore += 2;
    if (answers[8]) ctScore += 2;
    if (answers[9]) csScore += 2;


    recommendedDegree = (csScore > ctScore) ? "Computer Science" : "Computer Technology";
}

std::string DegreeRecommendation::GetRecommendedDegree() const
{
    return recommendedDegree;
}

std::pair<double, double> DegreeRecommendation::GetDegreePercentages() const
{
    int totalScore = csScore + ctScore;
    double csPercentage = static_cast<double>(csScore) / totalScore * 100;
    double cePercentage = static_cast<double>(ctScore) / totalScore * 100;
    return std::make_pair(csPercentage, cePercentage);
}

MajorSelectionLogic::MajorSelectionLogic(const std::string& degree) : degree(degree)
{
    if (degree == "Computer Science") {
        majors = { "Software Engineering", "Business Information Systems", "Knowledge Engineering", "High Performance Computing" };
        majorQuestions = {
            {"Software Engineering", {"Are you interested in developing and maintaining software applications?", "Do you enjoy working in teams to solve complex problems?"}},
            {"Business Information Systems", {"Are you interested in the intersection of technology and business processes?", "Do you like analyzing data to improve business strategies?"}},
            {"Knowledge Engineering", {"Are you interested in designing systems that can mimic human decision-making?", "Do you enjoy working with AI and machine learning technologies?"}},
            {"High Performance Computing", {"Are you interested in optimizing software to run efficiently on powerful computer systems?", "Do you like solving computational challenges?"}}
        };
    }
    else if (degree == "Computer Technology") {
        majors = { "Embedded Systems", "Communication and Networking", "Cyber Security" };
        majorQuestions = {
            {"Embedded Systems", {"Do you enjoy working with both hardware and software components?", "Are you interested in building devices that interact with the physical world?"}},
            {"Communication and Networking", {"Are you interested in understanding how data is transmitted over networks?", "Do you enjoy configuring and managing network systems?"}},
            {"Cyber Security", {"Are you interested in learning how to protect systems from cyber threats and attacks?", "Do you enjoy problem-solving and critical thinking in high-pressure situations?"}}
        };
    }
}
// Function to display clear and concise information about a specific degree
void DisplayDegreeInfo(const std::string& degree) {
    if (degree == "Computer Science") {
        std::cout << "\n--- Computer Science Degree ---\n";
        std::cout << "Overview:\n";
        std::cout << "Focuses on the study of computers and computational systems. This degree covers programming, algorithms, and software development.\n";
        std::cout << "\nCore Topics:\n";
        std::cout << "- Programming: Learn various coding languages such as C++, Python, and Java.\n";
        std::cout << "- Algorithms and Data Structures: Understand how to efficiently manage and process data.\n";
        std::cout << "- Software Engineering: Develop skills in designing and maintaining software applications.\n";
        std::cout << "- Operating Systems: Explore how operating systems manage hardware and software resources.\n";
        std::cout << "\nCareer Opportunities:\n";
        std::cout << "- Software Developer\n";
        std::cout << "- Systems Analyst\n";
        std::cout << "- Data Scientist\n";
        std::cout << "\nTypical Courses:\n";
        std::cout << "- Introduction to Programming\n";
        std::cout << "- Algorithms and Complexity\n";
        std::cout << "- Database Systems\n";
        std::cout << "- Computer Networks\n";
    }
    else if (degree == "Computer Technology") {
        std::cout << "\n--- Computer Technology Degree ---\n";
        std::cout << "Overview:\n";
        std::cout << "Focuses on practical applications of technology, including hardware, networking, and IT support.\n";
        std::cout << "\nCore Topics:\n";
        std::cout << "- Computer Hardware: Understand the components and functioning of computer systems.\n";
        std::cout << "- Networking: Learn about designing, implementing, and managing networks.\n";
        std::cout << "- IT Support: Develop skills to provide technical support and resolve issues.\n";
        std::cout << "- Systems Analysis: Analyze and improve IT systems and processes.\n";
        std::cout << "\nCareer Opportunities:\n";
        std::cout << "- IT Support Specialist\n";
        std::cout << "- Network Administrator\n";
        std::cout << "- Systems Technician\n";
        std::cout << "\nTypical Courses:\n";
        std::cout << "- Introduction to Computer Hardware\n";
        std::cout << "- Networking Fundamentals\n";
        std::cout << "- IT Project Management\n";
        std::cout << "- Systems Integration\n";
    }
    else {
        std::cout << "\nInformation not available for the specified degree.\n";
    }
}
const std::vector<std::string>& MajorSelectionLogic::GetMajors() const
{
    return majors;
}

std::pair<std::string, std::string> MajorSelectionLogic::GetMajorQuestions(const std::string& major) const
{
    auto it = majorQuestions.find(major);
    if (it != majorQuestions.end()) {
        return it->second;
    }
    return { "Are you interested in " + major + "?", "Do you find this field exciting?" };
}


std::string GetMajorRoadmap(const std::string& major)
{
    std::map<std::string, std::vector<std::string>> roadmaps = {
        {"Software Engineering", {
             "1. Master the Basics: \n Learn Core Programming Languages: Focus on languages like Python, Java, or C++.\nUnderstand Data Structures and Algorithms: These are crucial for problem-solving and coding interviews.",
             "2. Build Projects:\nStart Small: Create simple projects to apply what you’ve learned.\nGradually Increase Complexity: Work on more complex projects as you gain confidence.",
             "3. Use Version Control:\nLearn Git: It’s essential for collaboration and managing code.",
             "4. Study System Design:\nUnderstand How Systems Work: Learn about scalable and efficient system design.",
             "5. Stay Updated:\nFollow Tech Trends: Keep up with the latest technologies and tools.",
             "6. Practice Coding:\nUse Online Platforms: Practice coding problems on LeetCode, HackerRank, or CodeSignal.",
             "7. Develop Soft Skills:\nCommunication: Improve your ability to explain technical concepts.\nTeamwork: Learn to work effectively in a team.",
             "8. Seek Internships:\nGain Real-World Experience: Internships provide valuable industry experience.",
             "9. Network:\nJoin Tech Communities: Attend meetups, join online forums, and connect with professionals.",
            "10. Prepare for Interviews:\nMock Interviews: Practice with friends or use platforms like Pramp."
        }},
        {"Knowledge Engineering", {
             "1. Understand Core Concepts:\nFocus on key topics like databases, ERP, and data management.",
            "2. Follow a Structured Curriculum:\nUse textbooks, online courses, or university syllabi to guide your study.",
            "3. Hands-On Practice:\nApply concepts through case studies, projects, or internships.",
            "4. Stay Updated:\nFollow industry trends and new technologies in BIS.",
            "5. Group Study:\nCollaborate with peers for discussions and problem-solving.",
            "6. Focus on Tools:\nLearn popular BIS tools like SAP, Oracle, and Microsoft Dynamics.",
            "7. Seek Expert Guidance:\nAttend workshops or consult professionals for insights.",
            "8. Review Regularly:\nConsistently revisit key concepts to reinforce learning."
        }},
        {"Cyber Security", {
            "1. Learn Basics:\nStudy encryption, firewalls, and protocols.",
            "2. Understand Threats:\nLearn about common attacks and vulnerabilities.",
            "3. Use Security Tools:\nFamiliarize yourself with intrusion detection and scanning tools.",
            "4. Practice Skills:\nSet up secure networks and perform basic penetration tests.",
            "5. Know Compliance:\nUnderstand regulations like GDPR and HIPAA.",
            "6. Stay Updated:\nFollow the latest in security trends and threats.",
            "7. Get Certified:\nConsider certifications like CompTIA Security+ or CISSP."
        }},
        {"High Performance Computing ", {
            "1. Understand Basics:\nLearn parallel and distributed computing fundamentals.",
            "2. Learn Key Languages:\nFocus on C, C++, and Python for HPC.",
            "3. Explore Parallel Programming:\nStudy MPI, OpenMP, and CUDA.",
            "4. Understand HPC Architectures:\nLearn about multi-core processors and clusters.",
            "5. Hands-On Practice:\nWork on simple parallel programming projects.",
            "6. Use HPC Platforms:\nGain experience with Linux clusters or cloud HPC services.",
            "7. Study Applications:\nExplore how HPC is used in real-world scenarios.",
            "8. Stay Updated:\nFollow the latest trends and advancements in HPC."
        }},
        {"Embedded Systems", {
            "1. Learn Basics:\nStudy microcontrollers and RTOS.",
            "2. Master Programming:\nFocus on C and C++.",
            "3. Get Hands-On:\nWork with Arduino or Raspberry Pi.",
            "4. Understand Hardware:\nLearn about sensors and actuators.",
            "5. Explore Protocols:\nStudy I2C, SPI, and UART.",
            "6. Build Projects:\nApply knowledge in practical projects.",
            "7. Stay Current:\nFollow trends in embedded systems and IoT."
        }},
        {"Communication and Networking", {
            "1. Learn Basics:\nStudy encryption, firewalls, and protocols.",
            "2. Understand Threats:\nLearn about common attacks and vulnerabilities.",
            "3. Use Security Tools:\nFamiliarize yourself with intrusion detection and scanning tools.",
            "4. Practice Skills:\nSet up secure networks and perform basic penetration tests.",
            "5. Know Compliance:\nUnderstand regulations like GDPR and HIPAA.",
            "6. Stay Updated:\nFollow the latest in security trends and threats.",
            "7. Get Certified:\nConsider certifications like CompTIA Security+ or CISSP."
        }}
    };


    auto it = roadmaps.find(major);
    if (it != roadmaps.end()) {
        // Join the vector elements into a single string
        std::ostringstream roadmapStream;
        for (const auto& step : it->second) {
            roadmapStream << step << "\n";
        }
        return roadmapStream.str();
    }
    return "Roadmap not available for this major.";
}

bool isValidInput(const std::string& input) {
    std::string lowercaseInput = input;
    std::transform(lowercaseInput.begin(), lowercaseInput.end(), lowercaseInput.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return lowercaseInput == "y" || lowercaseInput == "n" || lowercaseInput == "yes" || lowercaseInput == "no" || lowercaseInput == "back";
}
bool isPositiveAnswer(const std::string& input) {
    std::string lowercaseInput = input;
    std::transform(lowercaseInput.begin(), lowercaseInput.end(), lowercaseInput.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return lowercaseInput == "y" || lowercaseInput == "yes";
}



std::string GetMajorInfo(const std::string& major)
{
    std::map<std::string, std::string> majorInfo = {
        {"Software Engineering", "Software Engineering focuses on the design, development, and maintenance of complex software systems. It combines principles from computer science, engineering, and mathematics to create reliable, efficient, and scalable software solutions."},
        {"Business Information Systems", "Business Information Systems (BIS) focuses on integrating technology with business processes to improve decision-making and efficiency. Students learn to design, implement, and manage information systems, gaining skills in programming, database management, and IT governance. Career opportunities include roles like IT project manager, systems analyst, and business process analyst"},
        {"Knowledge Engineering", "Knowledge Engineering focuses on creating systems that replicate human decision-making by using artificial intelligence. It involves translating expert knowledge into rules and data structures that computers can understand and use to solve complex problems. This field is essential in areas like healthcare, finance, and customer service, where it helps automate decision-making processes and improve efficiency."},
        {"Cybersecurity", "Cybersecurity is the practice of protecting systems, networks, and programs from digital attacks. It involves implementing strong security measures to prevent, detect, and respond to threats in the ever-evolving landscape of information technology."},
        {"High Performance Computing", "High Performance Computing (HPC) involves using powerful processors and computer clusters to solve complex problems at extremely high speeds. It is essential for tasks that require significant computational power, such as scientific simulations, data analysis, and machine learning. HPC systems can process massive datasets and perform calculations much faster than standard computers, making them crucial in fields like weather forecasting, genomics, and financial modeling"},
        {"Embedded Systems", "Embedded Systems involve integrating hardware and software to perform specific functions within larger systems.These systems are used in various applications like automotive controls, medical devices, and consumer electronics.They are designed for real - time processing and often operate with minimal human intervention."},
        {"Communication and Networking", "Communication and Networking focuses on connecting devices and systems to share data efficiently. This field covers the design, implementation, and management of networks, including local, wide-area, and mobile networks. Key topics include network protocols, data transmission, and network security."}
    };

    auto it = majorInfo.find(major);
    if (it != majorInfo.end()) {
        return it->second;
    }
    return "Information not available for this major.";
}
void DisplayMajorInfo(const std::string& major)
{
    const int width = 110;
    const std::string separator(width, '-');
    const std::string title = "Major: " + major;

    // Display title
    std::cout << separator << std::endl;
    std::cout << std::setw((width + title.length()) / 2) << title << std::endl;
    std::cout << separator << std::endl << std::endl;

    // Display major info
    std::cout << "Description:" << std::endl;
    std::cout << GetMajorInfo(major) << std::endl << std::endl;


    std::cout << std::endl << separator << std::endl;
}

std::string GetMajorOpportunity(const std::string& major)
{
    std::map<std::string, std::string> opportunity = {
        {"Software Engineering", "1. Front-end Developer\n2. Back-end Developer\n3. Full-stack Developer\n4. iOS Developer\n5. Android Developer\n6. Cross-platform Developer\n7. Data Engineer\n8. Big Data Engineer\n9. Machine Learning Engineer\n10. AI Researcher\n11. Cloud Engineer\n12. DevOps Engineer\n13. Security Engineer\n14. Ethical Hacker\n15. Embedded Software Engineer\n16. Firmware Engineer\n17. Game Developer\n18. Graphics Programmer\n19. Software Architect\n20. Enterprise Developer\n21. Startup Engineer\n22. CTO (Chief Technology Officer)\n23. R&D Engineer\n24. Freelance Developer\n25. Software Consultant"},
        {"Business Information Systems", "1. Business Analyst\n2. Systems Analyst  \n3. IT Project Manager  \n4. Data Analyst  \n5. ERP Consultant  \n6. Information Systems Manager  \n7. Web Developer  \n8. IT Business Strategist\n9. Software Consultant\n10. Cybersecurity Analyst"},
        {"Knowledge Engineering", "1. Knowledge Engineer  \n2. Artificial Intelligence (AI) Specialist  \n3. Machine Learning Engineer  \n4. Data Scientist  \n5. Natural Language Processing (NLP) Engineer  \n6. Ontology Engineer  \n7. Semantic Web Developer  \n8. Expert Systems Developer  \n9. Research Scientist  \n10. Cognitive Computing Engineer"},
        {"High Performance Computing", "1. HPC Engineer\n2. HPC Systems Administrator\n3. Parallel Computing Specialist\n4. HPC Software Developer\n5. HPC Architect\n6. Computational Scientist\n7. Data Center Engineer\n8. GPU Programmer\n9. HPC Analyst\n10. Supercomputing Engineer\n11. Cluster Administrator\n12. Performance Optimization Engineer"},
        {"Embedded Systems", "1. Embedded Systems Engineer\n2. Firmware Engineer\n3. Embedded Software Developer\n4. Hardware Engineer\n5. Embedded Linux Engineer\n6. Microcontroller Programmer\n7. FPGA Developer\n8. IoT (Internet of Things) Engineer\n9. Real-Time Systems Engineer\n10. Embedded Systems Architect\n11. Automotive Embedded Engineer\n12. Robotics Engineer"},
        {"Communication and Networking", "1. Network Engineer\n2. Telecommunications Engineer\n3. Network Administrator\n4. VoIP Engineer\n5. Wireless Communication Engineer\n6. Network Architect\n7. Systems Engineer (Networking)\n8. Network Security Engineer\n9. Communication Systems Engineer\n10. Network Support Specialist\n11. Cloud Networking Engineer\n12. Data Communications Analyst"}
    };


    auto it = opportunity.find(major);
    if (it != opportunity.end()) {
        return it->second;
    }
    return "Opportunity not available for this major.";
}
// Add this function to get subjects for each major and year
std::vector<std::string> getSubjects(const std::string& major, int year) {
    std::map<std::string, std::map<int, std::vector<std::string>>> subjectsByMajorAndYear = {
        {"Software Engineering", {
            {1, {"major will be choose at third year"}},
            {2, { "major will be choose at third year"}},
            {3, {"Web Technology", "Software Testing", "Operating Systems", "Computer Networks"}},
            {4, {"Software Project Management", "Project Management", "Cloud Computing", "Data Science and Machine Learning"}},
            { 5, {"Human Computer Interation", "Artificial Intelligence", "Advanced Software Engineering", "Data processing technquies in distributed systems"} }
        }},
        {"Business Information Systems", {
            {1, {"major will be choose at third year" }},
            {2, { "major will be choose at third year"}},
            {3, {"Data Analytics", "Data Science", "Software Development", "Cloud Computing"}},
            {4, {"Embedded Systems", "Internet of Things (IoT)", "Software Engineering Management" , "Machine Learning and Artificial Intelligence for business"}},
            {5, {"Blockchain Technology", "Advanced Software Design" ,"Software Quality Assurance(QA) ", "Augmented Reality (AR) and Virtual Reality (VR)" }}
        }},
        {"Cybersecurity", {
            {1, {"major will be choose at third year" }},
            {2, { "major will be choose at third year"}},
            {3, {"Network Security", "Cybersecurity Fundamentals", "Secure Software Development" , "Ethical Hacking and Penetration Testing" }},
            {4, {"Cyber Forensics", "Cloud Security", "Application Security", "Cybersecurity Policy and Strategy"}},
            {5, {"Data Science", "Advanced Cryptography", "Cloud Security" , "Artificial Intelligence in Cybersecurity"}}
        }},
        {"Knowledge Engineering", {
            {1, {"major will be choose at third year" }},
            {2, { "major will be choose at third year"}},
            {3, {"Knowledge Representation", "Database Systems for Knowledge Management", "Artificial Intelligence and Machine Learning", "Human-Computer Interaction (HCI) for Knowledge Systems"}},
            {4, {"Knowledge Discovery and Data Mining", "Decision Support Systems", "Knowledge Management Systems", "Knowledge Discovery and Data Mining"}},
            {5, {"Global Knowledge Systems", "Advanced Knowledge Engineering Techniques", "Knowledge Engineering Project Management", "Ethics and Legal Issues in Knowledge Engineering"}}
      }},
        {"High Performing Computing", {
            {1, { "major will be choose at third year"}},
            {2, { "major will be choose at third year"}},
            {3, {"Parallel Computing", "Operating Systems", "Operating System", "Computer Architecture"}},
            {4, {"Performance Engineering", "Distributed Systems", "Data Management and Storage", "High-Performance Computing (HPC) Systems"}},
            { 5, {"Advanced Parallel Programming", "Grid Computing", "Cybersecurity in HPC", "Machine Learning and Data Analysis"} }
        }},
        {"Embedded Systems", {
            {1, {"major will be choose at third year" }},
            {2, { "major will be choose at third year"}},
            {3, {"Embedded Systems Design", "Digital Logic Design", "Embedded Systems Programming", "Microcontroller and Microprocessor Systems"}},
            {4, {"Advanced Embedded Systems", "Power Management in Embedded Systems", "System-on-Chip (SoC) Design", "Embedded Networking and Communication"}},
            {5, {"Embedded Systems Security", "Advanced Sensor Integration", "Industrial Embedded Systems", "Embedded Systems Testing and Debugging"}}
        }},
        {"Communication and Networking",{
           {1, {"major will be choose at third year" }},
           {2, { "major will be choose at third year"}},
           {3, {"Communication Systems", "Computer Networks", "Network Protocols", "Digital Signal Processing (DSP)"}},
           {4, {"Advanced Networking", "Network Security", "Optical Networks", "Wireless Networks and Mobile Communications"}},
           {5, {"Next-Generation Networking", "Cloud Computing and Networking", "Network Management and Automation", "Advanced Wireless Communication Systems"}}
        } },
    };

    auto majorIt = subjectsByMajorAndYear.find(major);
    if (majorIt != subjectsByMajorAndYear.end()) {
        auto yearIt = majorIt->second.find(year);
        if (yearIt != majorIt->second.end()) {
            return yearIt->second;
        }
    }
    return { "Subjects not available for this major and year." };
}


struct Scholarship {
    std::string name;
    std::string description;
};

std::map<std::string, std::map<int, std::vector<Scholarship>>> scholarshipDatabase = {
    {"Software Engineering", {
        {1, {
            {"Google Scholarship", "A prestigious scholarship for first-year Software Engineering students, providing financial aid and mentorship."},
            {"ACM-W Scholarship", "Supports women in computing by covering costs for conferences and events."}
        }},
        {2, {
            {"Facebook Engineering Excellence", "Awarded to second-year Software Engineering students excelling in their studies."}
        }},
        {3, {}}, // No scholarships for Year 3
        {4, {
            {"Microsoft Diversity Scholarship", "Supports diverse candidates in their final year of Software Engineering."}
        }},
    }},
    {"Business Information Systems", {
        {1, {}}, // No scholarships for Year 1
        {2, {
            {"McKinsey Emerging Scholars", "Offered to second-year students with strong leadership potential."}
        }},
        {3, {
            {"SAP Scholarship for Business Innovators", "Awarded to third-year students showing innovation in business technology."}
        }},
        {4, {
            {"Deloitte Technology Scholars", "Supports final-year students with a focus on business information systems."}
        }},
    }},
    {"Knowledge Engineering", {
        {1, {
            {"AI Research Fellowship", "Supports first-year Knowledge Engineering students interested in AI research."}
        }},
        {2, {
            {"IBM Watson Scholarship", "Awarded to second-year students focusing on cognitive computing and AI."}
        }},
        {3, {}}, // No scholarships for Year 3
        {4, {
            {"DeepMind Scholarship", "Covers the cost of final-year tuition for students specializing in machine learning."}
        }},
    }},
    {"High Performance Computing", {
        {1, {}}, // No scholarships for Year 1
        {2, {
            {"NVIDIA GPU Research Grant", "Offered to second-year students engaged in GPU computing research."}
        }},
        {3, {
            {"Intel HPC Scholarship", "Supports third-year students with a focus on high-performance computing systems."}
        }},
        {4, {}}, // No scholarships for Year 4
    }},
    {"Embedded Systems", {
        {1, {
            {"ARM Embedded Systems Scholarship", "Offered to first-year students with an interest in embedded systems design."}
        }},
        {2, {}}, // No scholarships for Year 2
        {3, {
            {"Texas Instruments Embedded Innovation", "Supports third-year students working on embedded systems projects."}
        }},
        {4, {
            {"Qualcomm Scholarship", "Provides financial support for final-year students specializing in embedded systems."}
        }},
    }},
    {"Communication and Networking", {
        {1, {
            {"Cisco Networking Scholarship", "Provides support to first-year students studying networking technologies."}
        }},
        {2, {}}, // No scholarships for Year 2
        {3, {
            {"Huawei Communications Scholarship", "Awarded to third-year students with a focus on telecommunications."}
        }},
        {4, {
            {"Ericsson Scholarship for Network Engineers", "Supports final-year students specializing in communication networks."}
        }},
    }},
};

int getValidIntInput(int min, int max) {
    int choice;
    while (true) {
        if (std::cin >> choice && choice >= min && choice <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
    }
}
void DisplayScholarships(const std::string& major, int year) {
    auto majorIt = scholarshipDatabase.find(major);
    if (majorIt != scholarshipDatabase.end()) {
        auto yearIt = majorIt->second.find(year);
        if (yearIt != majorIt->second.end() && !yearIt->second.empty()) {
            std::cout << "\nAvailable scholarships for " << major << " (Year " << year << "):\n";
            for (const auto& scholarship : yearIt->second) {
                std::cout << "- " << scholarship.name << ": " << scholarship.description << "\n";
            }
        }
        else {
            std::cout << "\nNo scholarships available for " << major << " (Year " << year << ").\n";
        }
    }
    else {
        std::cout << "\nMajor not found in the scholarship database.\n";
    }
}


int main()
{
    QuestionnaireLogic questionnaire;
    std::vector<std::string> userAnswers;

    while (true) {
        std::cout << "Choose an option:\n";
        std::cout << "1. View available bachelor's degrees\n";
        std::cout << "2. Take the degree recommendation questionnaire\n";
        std::cout << "3. Learn about Computer Science and Computer Technology degrees\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";

        int choice = getValidIntInput(1, 4);

        if (choice == 1) {
            displayBachelorDegrees();
        }
        else if (choice == 2) {
            break;  // Proceed to the questionnaire
        }
        else if (choice == 3) {
            std::cout << "\nChoose a degree to learn more about:\n";
            std::cout << "1. Computer Science\n";
            std::cout << "2. Computer Technology\n";
            std::cout << "Enter your choice (1-2): ";

            int degreeChoice = getValidIntInput(1, 2);
            std::string chosenDegree = (degreeChoice == 1) ? "Computer Science" : "Computer Technology";

            std::cout << "\nInformation about " << chosenDegree << " degree:\n";
            DisplayDegreeInfo(chosenDegree);
        }
        else if (choice == 4) {
            std::cout << "Thank you for using our program. Goodbye!\n";
            return 0;
        }
    }
    // Ask questions and get answers
    while (!questionnaire.IsFinished())
    {
        std::cout << questionnaire.GetCurrentQuestion() << " (y/n/back): ";
        std::string answer;
        std::cin >> answer;

        while (!isValidInput(answer)) {
            std::cout << "Invalid input. Please enter 'y', 'n', or 'back': ";
            std::cin >> answer;
        }

        if (answer == "back") {
            if (!userAnswers.empty()) {
                userAnswers.pop_back();
                questionnaire = QuestionnaireLogic(); // Reset questionnaire
                for (const auto& ans : userAnswers) {
                    if (isPositiveAnswer(ans)) {
                        questionnaire.AnswerYes();
                    }
                    else {
                        questionnaire.AnswerNo();
                    }
                }
            }
            else {
                continue;
            }
        }
        else {
            userAnswers.push_back(answer);
            if (isPositiveAnswer(answer)) {
                questionnaire.AnswerYes();
            }
            else {
                questionnaire.AnswerNo();
            }
        }
    }
    // Get degree recommendation and percentages
    DegreeRecommendation recommendation(questionnaire.GetAnswers());
    std::string recommendedDegree = recommendation.GetRecommendedDegree();
    auto percentages = recommendation.GetDegreePercentages();

    std::cout << "\nBased on your answers:\n";
    std::cout << "Computer Science: " << std::fixed << std::setprecision(1) << percentages.first << "%\n";
    std::cout << "Computer Technology: " << std::fixed << std::setprecision(1) << percentages.second << "%\n";

    if (std::isnan(percentages.first) || std::isnan(percentages.second) ||
        (percentages.first == 0 && percentages.second == 0)) {
        std::cout << "\nIt seems you answered 'no' to all questions. Let's explore both degrees.\n";
        std::cout << "Which degree would you like to explore further?\n";
        std::cout << "1. Computer Science\n";
        std::cout << "2. Computer Technology\n";
        std::cout << "Enter your choice (1-2): ";


        int degreeChoice = getValidIntInput(1, 2);
        recommendedDegree = (degreeChoice == 1) ? "Computer Science" : "Computer Technology";
    }
    else if (percentages.first == 100 && percentages.second == 100) {
        std::cout << "\nIt seems you answered 'yes' to all questions. Both degrees might be a good fit for you.\n";
        std::cout << "Which degree would you like to explore further?\n";
        std::cout << "1. Computer Science\n";
        std::cout << "2. Computer Technology\n";
        std::cout << "Enter your choice (1-2): ";

        int degreeChoice = getValidIntInput(1, 2);
        recommendedDegree = (degreeChoice == 1) ? "Computer Science" : "Computer Technology";
    }

    std::cout << "Recommended degree: " << recommendedDegree << "\n";
    // Allow user to choose between the two degrees
    std::cout << "\nWould you like to explore the recommended degree or choose a different one?\n";

    std::cout << "1. Explore " << recommendedDegree << "\n";
    std::cout << "2. Choose a different degree\n";
    std::cout << "Enter your choice (1-2): ";

    int degreeChoice = getValidIntInput(1, 2);
    std::string chosenDegree = recommendedDegree;

    if (degreeChoice == 2) {
        std::cout << "\nWhich degree would you like to explore?\n";
        std::cout << "1. Computer Science\n";
        std::cout << "2. Computer Technology\n";
        std::cout << "Enter your choice (1-2): ";

        degreeChoice = getValidIntInput(1, 2);
        chosenDegree = (degreeChoice == 1) ? "Computer Science" : "Computer Technology";
    }

    MajorSelectionLogic majorSelection(chosenDegree);
    std::cout << "\nPossible majors for " << chosenDegree << ":\n";
    for (const auto& major : majorSelection.GetMajors())
    {
        std::cout << "- " << major << "\n";
    }
    bool foundScholarships = false;

    while (true) {
        std::cout << "\nDo you want to check available scholarships or proceed to the major-specific questions?\n";
        std::cout << "1. Check available scholarships\n";
        std::cout << "2. Proceed to the major-specific questions\n";
        std::cout << "Enter your choice (1-2): ";

        int scholarshipChoice = getValidIntInput(1, 2);

        if (scholarshipChoice == 1) {
            std::cout << "Enter the number of the major to check scholarships: ";
            int majorNumber = getValidIntInput(1, majorSelection.GetMajors().size());
            std::string selectedMajor = majorSelection.GetMajors()[majorNumber - 1];

            std::cout << "Enter the year of study (1-4): ";
            int year = getValidIntInput(1, 4);

            DisplayScholarships(selectedMajor, year);
            foundScholarships = true;
        }
        else if (scholarshipChoice == 2) {
            if (foundScholarships) {
                std::cout << "Proceeding to the major-specific questions...\n";
            }
            break;
        }
    }

    // Ask questions to choose a major
    std::vector<int> majorScores(majorSelection.GetMajors().size(), 0);
    std::vector<std::string> majorAnswers;
    int i = 0;
    int j = 0; // Index for questions

    while (i < majorSelection.GetMajors().size())
    {
        auto questions = majorSelection.GetMajorQuestions(majorSelection.GetMajors()[i]);

        while (j < 2) // Assuming two questions per major
        {
            const std::string& question = (j == 0) ? questions.first : questions.second;
            std::cout << "\n" << question << " (y/n/back): ";
            std::string answer;
            std::cin >> answer;

            while (!isValidInput(answer)) {
                std::cout << "Invalid input. Please enter 'y', 'n', or 'back': ";
                std::cin >> answer;
            }

            if (answer == "back") {
                if (j > 0) {
                    // Go back to the previous question within the same major
                    j--;
                    if (!majorAnswers.empty()) {
                        majorAnswers.pop_back();
                    }
                }
                else if (i > 0) {
                    // Go back to the previous major if we are on the first question
                    i--;
                    j = 1; // Go back to the second question of the previous major
                    if (!majorAnswers.empty()) {
                        majorAnswers.pop_back();
                    }
                }
                continue;
            }
            else {
                majorAnswers.push_back(answer);
                if (isPositiveAnswer(answer)) {
                    majorScores[i] += 1;
                }
                j++;
            }
        }

        i++;
        j = 0; // Reset question index for the next major
    }


    // Find the recommended major
    auto maxScore = std::max_element(majorScores.begin(), majorScores.end());
    std::string recommendedMajor = majorSelection.GetMajors()[std::distance(majorScores.begin(), maxScore)];

    bool allYes = std::all_of(majorScores.begin(), majorScores.end(), [](int score) { return score == 1; });
    bool allNo = std::all_of(majorScores.begin(), majorScores.end(), [](int score) { return score == 0; });

    if (allNo) {
        std::cout << "\nIt seems you answered 'no' to all questions about majors.\n";
        std::cout << "Let's explore all the majors for " << chosenDegree << ".\n";
        std::cout << "Which major would you like to learn more about?\n";
        for (size_t i = 0; i < majorSelection.GetMajors().size(); ++i) {
            std::cout << i + 1 << ". " << majorSelection.GetMajors()[i] << "\n";
        }
        std::cout << "Enter your choice (1-" << majorSelection.GetMajors().size() << "): ";
        int majorChoice = getValidIntInput(1, majorSelection.GetMajors().size());
        recommendedMajor = majorSelection.GetMajors()[majorChoice - 1];
    }
    else if (allYes) {
        std::cout << "\nIt seems you answered 'yes' to all questions about majors.\n";
        std::cout << "All majors in " << chosenDegree << " might be a good fit for you.\n";
        std::cout << "Which major would you like to explore further?\n";
        for (size_t i = 0; i < majorSelection.GetMajors().size(); ++i) {
            std::cout << i + 1 << ". " << majorSelection.GetMajors()[i] << "\n";
        }
        std::cout << "Enter your choice (1-" << majorSelection.GetMajors().size() << "): ";
        int majorChoice = getValidIntInput(1, majorSelection.GetMajors().size());
        recommendedMajor = majorSelection.GetMajors()[majorChoice - 1];
    }
    else {
        auto maxScore = std::max_element(majorScores.begin(), majorScores.end());
        recommendedMajor = majorSelection.GetMajors()[std::distance(majorScores.begin(), maxScore)];
        std::cout << "\nBased on your answers, we recommend the major: " << recommendedMajor << "\n";
    }



    // New options after choosing major
    while (true) {
        std::cout << "\nWhat would you like to do next?\n";
        std::cout << "1. Learn more about " << recommendedMajor << "\n";
        std::cout << "2. View roadmap and career guide for " << recommendedMajor << "\n";
        std::cout << "3. Go back to major selection\n";
        std::cout << "4. Go back to degree question\n"; // New option added here
        std::cout << "5. Opportunity\n";
        std::cout << "6. View subjects for " << recommendedMajor << "\n";
        std::cout << "7. Exit\n"; // Adjusted numbering to accommodate the new option
        std::cout << "Enter your choice (1-7): "; // Adjusted to reflect the new total number of options

        int choice = getValidIntInput(1, 7); // Adjusted to include the new option

        if (choice == 1) {
            std::cout << "\nInformation about " << recommendedMajor << ":\n";
            DisplayMajorInfo(recommendedMajor);
        }
        else if (choice == 2) {
            std::cout << "\nRoadmap for " << recommendedMajor << ":\n";
            std::cout << GetMajorRoadmap(recommendedMajor) << "\n";
            std::cout << "\nCareer Guide:\n";
            std::cout << "This is where you would provide career guide information for " << recommendedMajor << ".\n";
        }
        else if (choice == 3) {
            // Go back to major selection
            majorScores = std::vector<int>(majorSelection.GetMajors().size(), 0);
            majorAnswers.clear();

            // Re-run the major selection questions
            for (size_t i = 0; i < majorSelection.GetMajors().size(); ++i) {
                auto questions = majorSelection.GetMajorQuestions(majorSelection.GetMajors()[i]);

                for (const auto& question : { questions.first, questions.second }) {
                    while (true) {
                        std::cout << "\n" << question << " (y/n/back): ";
                        std::string answer;
                        std::cin >> answer;
                        while (!isValidInput(answer)) {
                            std::cout << "Invalid input. Please enter 'y', 'n', or 'back': ";
                            std::cin >> answer;
                        }
                        if (answer == "back") {
                            if (!majorAnswers.empty()) {
                                majorAnswers.pop_back();
                                if (i > 0) i -= 1; // Go back to previous major
                                break;
                            }
                        }
                        else {
                            majorAnswers.push_back(answer);
                            if (isPositiveAnswer(answer)) {
                                majorScores[i] += 1;
                            }
                            break;
                        }
                    }
                }
            }

            // Find the new recommended major
            maxScore = std::max_element(majorScores.begin(), majorScores.end());
            recommendedMajor = majorSelection.GetMajors()[std::distance(majorScores.begin(), maxScore)];

            std::cout << "\nBased on your answers, we recommend the major: " << recommendedMajor << "\n";
        }
        else if (choice == 4) { // New option handling
            // Go back to degree question
            return main(); // Restart the main function to go back to the degree selection
        }
        else if (choice == 5) {
            std::cout << "\nBased on your major chosen, The opportunities you can get are: " << GetMajorOpportunity(recommendedMajor) << "\n";
        }
        else if (choice == 6) {
            std::cout << "\nChoose a year to view subjects for " << recommendedMajor << ":\n";
            std::cout << "1. First Year\n";
            std::cout << "2. Second Year\n";
            std::cout << "3. Third Year\n";
            std::cout << "4. Fourth Year\n";
            std::cout << "Enter your choice (1-4): ";

            int yearChoice = getValidIntInput(1, 4);
            std::vector<std::string> subjects = getSubjects(recommendedMajor, yearChoice);

            std::cout << "\nSubjects for " << recommendedMajor << " (Year " << yearChoice << "):\n";
            for (const auto& subject : subjects) {
                std::cout << "- " << subject << "\n";
            }
        }
        else if (choice == 7) { // Adjusted for the new exit option
            std::cout << "Thank you for using our program. Goodbye!\n";
            break;
        }
    }

    return 0;
}
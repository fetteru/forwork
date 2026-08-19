#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<iomanip>
#include<windows.h>   //SetConsoleOutputCP

using namespace std;

//成绩 -> 等级 / 绩点
struct GradeInfo {
    const char* grade;  //等级
    double point;       //绩点
};

GradeInfo toGrade(int score)
{
    if(score >= 95) return {"A+", 4.3};
    if(score >= 90) return {"A",  4.0};
    if(score >= 85) return {"A-", 3.7};
    if(score >= 81) return {"B+", 3.3};
    if(score >= 78) return {"B",  3.0};
    if(score >= 75) return {"B-", 2.7};
    //以下为补全的常见档位，请按你学校的标准修改
    if(score >= 72) return {"C+", 2.3};
    if(score >= 68) return {"C",  2.0};
    if(score >= 64) return {"C-", 1.7};
    if(score >= 60) return {"D",  1.0};
    return {"F", 0.0};
}

struct Course {
    string name;    //课程名
    double credit;  //学分
    int score;      //成绩
};

//读取grade.txt，返回课程列表；文件不存在则创建模板
vector<Course> loadGrades(const string& path)
{
    vector<Course> courses;
    ifstream fin(path);
    if(!fin)    //文件不存在 -> 创建一个带示例的模板
    {
        ofstream fout(path);
        fout << "#格式：课程名 学分 成绩（#开头的行为注释）\n";
        fout << "高等数学 4 92\n";
        fout << "大学英语 3 86\n";
        fout << "数据结构 4 78\n";
        fout.close();
        cout << "未找到 " << path << "，已创建模板文件，请编辑后重新运行。\n";
        cout << "本次先用模板示例数据计算：\n\n";
        fin.open(path);
    }

    string line;
    int lineNo = 0;
    while(getline(fin, line))
    {
        lineNo++;
        //去掉行首空格，跳过空行和注释行
        size_t pos = line.find_first_not_of(" \t\r\n");
        if(pos == string::npos || line[pos] == '#') continue;

        istringstream iss(line);
        Course c;
        if(iss >> c.name >> c.credit >> c.score && c.credit > 0 && c.score >= 0 && c.score <= 100)
        {
            courses.push_back(c);
        }
        else
        {
            cout << "[警告] 第" << lineNo << "行格式有误，已跳过: " << line << "\n";
        }
    }
    return courses;
}

int main()
{
    SetConsoleOutputCP(65001);   //控制台按UTF-8输出，文件也是UTF-8，两边统一
    vector<Course> courses = loadGrades("grade.txt");
    if(courses.empty())
    {
        cout << "grade.txt 中没有有效课程数据。\n";
        return 0;
    }

    double totalCredit = 0;       //总学分
    double totalWeighted = 0;     //Σ(学分×绩点)

    cout << left << setw(14) << "课程" << setw(7) << "学分"
         << setw(7) << "成绩" << setw(6) << "等级"
         << setw(7) << "绩点" << "加权绩点\n";
    cout << string(45, '-') << "\n";

    for(const Course& c : courses)
    {
        GradeInfo g = toGrade(c.score);
        double weighted = c.credit * g.point;   //该课加权绩点
        totalCredit += c.credit;
        totalWeighted += weighted;

        cout << left << setw(14) << c.name << setw(6) << c.credit
             << setw(6) << c.score << setw(5) << g.grade
             << setw(6) << g.point << weighted << "\n";
    }

    cout << string(45, '-') << "\n";
    if(totalCredit > 0)
    {
        double gpa = totalWeighted / totalCredit;
        cout << "总学分: " << totalCredit
             << "    加权绩点(GPA): " << fixed << setprecision(2) << gpa << "\n";
    }
    return 0;
}

#include "calculate.h"
#include <iostream>
#include <vector>
#include <algorithm>

int partition(std::vector<Tutor>& tutors, int left, int right) {
    Tutor pivot = tutors[right];
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (tutors[j] < pivot) {
            ++i;
            std::swap(tutors[i], tutors[j]);
        }
    }

    std::swap(tutors[i + 1], tutors[right]);
    return i + 1;
}

Tutor quickselect(std::vector<Tutor>& tutors, int left, int right, int k) {
    if (left == right)
        return tutors[left];

    int pivotIndex = partition(tutors, left, right);
    int rank = pivotIndex - left + 1;

    if (k == rank)
        return tutors[pivotIndex];
    else if (k < rank)
        return quickselect(tutors, left, pivotIndex - 1, k);
    else
        return quickselect(tutors, pivotIndex + 1, right, k - rank);
}

Tutor find_nth_largest(std::vector<Tutor>& tutors, int n) {
    int k = tutors.size() - n + 1;
    return quickselect(tutors, 0, tutors.size() - 1, k);
}

// A greedy DP algorithm using a priority queue
bool backtrack(std::vector<Tutor>& tutors, std::vector<StudentReference>& participants) {
    if(!participants.size()) {
        return true;
    }

    std::pop_heap(tutors.begin(), tutors.end());
    Tutor tutor = tutors.back();
    tutors.pop_back();

    // Create a copy and sort the participants because we are working with references
    std::vector<StudentReference> parts = participants;

    std::sort(parts.begin(), parts.end(), [&tutor](const StudentReference& s1, const StudentReference& s2){
        tutor.add_student(s1);
        int score1 = tutor.get_availability_score();
        tutor.pop_student();

        tutor.add_student(s2);
        int score2 = tutor.get_availability_score();
        tutor.pop_student();

        return score1 > score2;
    });

    for(auto it = parts.begin(); it != parts.end(); ++it) {
        StudentReference best_student = *it;
        participants.erase(it);
        tutor.add_student(best_student);

        // Store a reference to the tutor's student ID to find it later
        const QString student_id = tutor.get_student_id();
        tutors.push_back(tutor);
        std::push_heap(tutors.begin(), tutors.end());

        bool result = backtrack(tutors, participants);

        // Find back the tutor and remove the student
        auto found_tutor = std::find_if(tutors.begin(), tutors.end(), [&student_id](const Tutor& tutor) {
            return student_id == tutor.get_student_id();
        });

        (*found_tutor).pop_student();
        std::make_heap(tutors.begin(), tutors.end());
    }
}

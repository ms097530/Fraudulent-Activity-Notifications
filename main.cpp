// The activityNotifications function is implemented to solve the problem given at
// https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=sorting
// The function passes all tests given at the website
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int activityNotifications(vector<int> expenditure, int d) 
// in: expenditure, an vector of values in order of date
//     d, the number of days to look back to determine fraudulent activity
// out: the number of notifications for possible fraudulent activity sent
//      for the given days of expenditures
{
    int notificationCount = 0;    
    // subsection of expenditure to keep track of only necessary d days
    vector<int> subVec(expenditure.begin(), expenditure.begin()+d); 
    sort(subVec.begin(), subVec.end());     // initial sort of subvector
    int j = 0;
    int first = expenditure[j];  // to keep track of former leading value to remove each iteration
    int oddOrEven = d % 2;
    float average;
    // initial processing to calibrate data for further processing
    if (oddOrEven == 0) // even - need average of two middle numbers
    {
        average = (subVec[d/2] + subVec[(d/2)-1]) / 2.0;        
    }
    else    // odd
    {
        average = subVec[d/2];
    }
    
    if (float(expenditure[d]) >= 2.0 * average)
        ++notificationCount;
    ++j;

    // loop to process remainder of values
    for (int i = d+1; i < expenditure.size(); ++i, ++j)
    {        
        auto it = find(subVec.begin(), subVec.end(), first);
        subVec.erase(it);
        auto it2 = lower_bound(subVec.begin(), subVec.end(), expenditure[i-1]);
        // insert current tail at proper spot - maintaining sorting
        subVec.insert(it2, expenditure[i-1]);
        
        if (oddOrEven == 0) // even - need average of two middle numbers
        {
            average = (subVec[d/2] + subVec[(d/2)-1]) / 2.0;            
        }
        else    // odd
        {                      
            average = subVec[d/2];              
        }        
            
        if (float(expenditure[i]) >= 2.0 * average)
                ++notificationCount;
        first = expenditure[j];
    }
    
    return notificationCount;
}

int main()
{
    cout << "Expected: 0 " << "Actual: " << activityNotifications(vector<int> {1,2,3,4,4}, 4) << endl;
    return 0;
}
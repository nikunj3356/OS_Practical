#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> page_references = {4, 7, 1, 4, 9, 4, 2, 7, 9, 2};
    int num_frames = 4;
    vector<int> frames(num_frames, -1);

    unordered_map<int, int> page_frequency;
    for (int i = 0; i < page_references.size(); i++)
    {
        int page = page_references[i];
        if (find(frames.begin(), frames.end(), page) != frames.end())
        {
            page_frequency[page]++;
        }
        else if (find(frames.begin(), frames.end(), -1) != frames.end())
        {
            int index = find(frames.begin(), frames.end(), -1) - frames.begin();
            frames[index] = page;
            page_frequency[page] = 1;
        }
        else
        {
            int max_frequency = 0;
            int evict_page;
            for (int j = 0; j < num_frames; j++)
            {
                if (page_frequency[frames[j]] > max_frequency)
                {
                    max_frequency = page_frequency[frames[j]];
                    evict_page = frames[j];
                }
            }
            int index = find(frames.begin(), frames.end(), evict_page) - frames.begin();
            frames[index] = page;
            page_frequency.erase(evict_page);
            page_frequency[page] = 1;
        }
        cout << "Page Reference " << page << ": ";
        for (int j = 0; j < num_frames; j++)
        {
            cout << frames[j] << " ";
        }
        cout << endl;
    }
    return 0;
}
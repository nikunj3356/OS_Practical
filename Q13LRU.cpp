#include <iostream>
using namespace std;

int main()
{
	int num_pages, num_faults, pages[20], i, fault_count = 0;

	cout << "\nEnter the number of pages for which you want to calculate page faults: ";
	cin >> num_pages;

	cout << "\nEnter the reference string:\n";
	for (i = 0; i < num_pages; i++)
	{
		cout << "Page " << i + 1 << ": ";
		cin >> pages[i];
	}

	cout << "\nEnter the number of frames: ";
	cin >> num_faults;

	int frames[num_faults], frame_counts[num_faults];
	for (i = 0; i < num_faults; i++)
	{
		frames[i] = -1;
		frame_counts[i] = 0;
	}

	i = 0;
	while (i < num_pages)
	{
		int j = 0, flag = 0;
		while (j < num_faults)
		{
			if (pages[i] == frames[j])
			{
				flag = 1;
				frame_counts[j] = i + 1;
			}
			j++;
		}

		j = 0;
		cout << "\n***\n";
		cout << "Page " << pages[i] << " -->";
		if (flag == 0)
		{
			int min = 0, k = 0;
			while (k < num_faults - 1)
			{
				if (frame_counts[min] > frame_counts[k + 1])
					min = k + 1;
				k++;
			}
			frames[min] = pages[i];
			frame_counts[min] = i + 1;
			fault_count++;
			while (j < num_faults)
			{
				cout << "\t|" << frames[j] << "|";
				j++;
			}
		}
		i++;
	}

	cout << "\n***\n";
	cout << "\nPage Faults: " << fault_count << "\n";

	return 0;
}

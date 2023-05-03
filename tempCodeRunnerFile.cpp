
            std::cout << std::endl;
            std::cout << "Money Left: Rs " << money << std::endl;
        }
        return;
    }
}

void max_dist(int source, int money)
{
    for (int k = 0; k < CITIES; k++)
    {
        for (int i = 0; i < CITIES; i++)
        {
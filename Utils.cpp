#include "Utils.h"

std::vector<std::vector<std::shared_ptr<Entity>>> Utils::combineEntities(const std::vector<std::shared_ptr<Entity>>& entities, int permutationLength)
{
    std::vector<std::vector<std::shared_ptr<Entity>>> result;

    bool hasFinished = entities.size() < 1 || permutationLength > entities.size();
    std::vector<int> currentPermutation(permutationLength);

    for (size_t i = 1; i <= permutationLength; ++i)
    {
        currentPermutation[i-1] = i;
    }

    while (!hasFinished)
    {
        std::vector<std::shared_ptr<Entity>> permutation;
        permutation.reserve(permutationLength);

        for (auto index : currentPermutation) {
            permutation.push_back(entities[index - 1]);
        }

        result.emplace_back(std::move(permutation));

        hasFinished = true;

        for (int i = permutationLength - 1; i >= 0 ; --i)
            if (currentPermutation[i] < entities.size() - permutationLength + i + 1) {
                int j = currentPermutation[i] + 1;
                while (i <= permutationLength - 1)                
                    currentPermutation[i++] = j++;
                
                hasFinished = false;
                break;
            }
        
    }

    return std::move(result);
}

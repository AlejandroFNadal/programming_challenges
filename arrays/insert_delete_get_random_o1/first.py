class RandomizedSet:

    def __init__(self):
        self.data = {}

    def insert(self, val: int) -> bool:
        if self.data.get(val):
            return False
        else:
            self.data[val] = True
            return True
        

    def remove(self, val: int) -> bool:
        if self.data.get(val):
            self.data.pop(val, None)
            return True
        else:
            return False

    def getRandom(self) -> int:
        data_keys = list(self.data.keys())
        rindex = random.randrange(0, len(data_keys),1)
        return data_keys[rindex]


# Your RandomizedSet object will be instantiated and called as such:
# obj = RandomizedSet()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()

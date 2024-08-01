class DynamicArray:

    def _init_(self,cap=1):
        self.__capacity=cap
        self.__size=0
        self.__data=[None]*cap
        self.__resizeFactor=2

   
    def setResizeFactor(self,rf):
        self.__resizeFactor=rf

   
    def __isvalid(self,ind):
        if 0 <= ind < self.__size:
            return True
        else:
            return False

    def _getitem_(self, ind)-> int:
        if self.__isvalid(ind):
            return self.__data[ind]
        else:
            raise IndexError("Index out of bounds!")

    def _setitem_(self, ind,val):
        if self.__isvalid(ind):
            self.__data[ind]=val
        else:
            raise IndexError('Index out of bounds!')

    def _len_(self):
        return self.__size

    def _str_(self):
        if self.isEmpty():
            return "[]"
        else:
            l=[]
            for i in range(self.__size):
                l.append(self.__data[i])
            return ", ".join(map(str,l))

    
    def __resize(self):
        new_array=[None]*self._resizeFactor*self._size
        for i in range(self.__size):
            new_array[i]=self.__data[i]
        self._capacity=self.resizeFactor*self._capacity
        self.__data=new_array

    
    def isEmpty(self):
        return self.__size==0

    
    def append(self,val):
        if self._size<self._capacity:
            self._data[self._size]=val
            self.__size+=1
        else:
            self.__resize()
            self.append(val)

    
    def addAt(self,index,data):
        if index>self.__size:
            raise Exception("Index out of bounds!")
        if self.isEmpty() or self.__size==index:
            self.append(data)
        else:
            if self._size<self._capacity:
                for i in range(self.__size,index-1,-1):
                    self._data[i]=self._data[i-1]
                self.__data[index]=data
                self.__size+=1
            else:
                self.__resize()
                self.addAt(index,data)

   
    def pop(self):
        if self.isEmpty():
            raise Exception("Empty list!")
        else:
            self._data[self._size-1]=None
            self.__size-=1

    
    def removeAt(self,index):
        if self.isEmpty():
            raise Exception("Empty array!")
        elif index>=self.__size:
            raise Exception("Index Out of bounds!")
        else:
            if index==self.__size-1:
                self.pop()
            else:
                for i in range(index,self.__size):
                    self._data[i]=self._data[i+1]
                self.__size-=1

   
    def rotateOnce(self):
        if self.isEmpty():
            raise Exception("Empty array!")
        else:
            if self.__size==1:
                pass
            else:
                x=self._data[self._size-1]
                for i in range(self.__size-1,0,-1):
                    self._data[i]=self._data[i-1]
                self.__data[0]=x

    
    def rotate(self,k):
        if self.isEmpty():
            raise Exception("Empty array!")
        else:
            for i in range(k):
                self.rotateOnce()

   
    def reverse(self):
        if self.isEmpty():
            raise Exception("Empty array!")
        else:
            l=[]
            for i in range(self.__size-1,-1,-1):
                l.append(self.__data[i])
            self.__data=l
            del(l)

    
    def prepend(self,data):
        if self.isEmpty():
            raise Exception("Empty array!")
        else:
            self.addAt(0,data)

    
    def merge(self,arr):
        if self.isEmpty():
            raise Exception("Empty array!")
        if len(arr)==0:
            pass
        else:
            n1=len(arr)
            n2=self.__size
            i,j=0,0
            res_arr=[]
            while i+j<n2+n1:
                if i==n1:
                    res_arr.append(self.__data[j])
                    j+=1
                elif j==n2:
                    res_arr.append(arr[i])
                    i+=1
                else:
                    if arr[i]<self.__data[j]:
                        res_arr.append(arr[i])
                        i+=1
                    else:
                        res_arr.append(self.__data[j])
                        j+=1
            self.__data=res_arr
            self.__size+=len(arr)
            del(res_arr)

    
    def interleave(self,arr):
        if self.isEmpty():
            raise Exception("Empty array!")
        if len(arr)==0:
            pass
        else:
            l=[]
            n1=len(arr)
            n2=self.__size
            i,j=0,0
            while i+j<n1+n2:
                if i==n1:
                    l.append(self.__data[j])
                    j+=1
                elif j==n2:
                    l.append(arr[i])
                    i+=1
                else:
                    l.append(self.__data[j])
                    l.append(arr[i])
                    i+=1
                    j+=1
            self.__data=l
            del(l)
            self.__size+=len(arr)


    def midElement(self):
        if self.isEmpty():
            raise Exception("Empty array!")
        else:
            return self._data[(self._size)//2]

   
    def find(self,x):
        if self.isEmpty():
            raise Exception("Empty array!")
        else:
            for ind,i in enumerate(self.__data):
                if i==x:
                    return ind
            return -1


    def split(self,ind):
        if self.isEmpty():
            raise Exception("Empty array!")
        else:
            l2=DynamicArray()
            for i in range(ind,self.__size):
                l2.append(self.__data[i])
                self.__data[i]=None
            self.__size-=len(l2)
            l1 = DynamicArray()
            for i in range(ind):
                l1.append(self.__data[i])
            return (l1,l2)

arr=DynamicArray()
arr.append(2)
arr.append(4)
arr.append(5)
arr.append(6)
print(arr)
arr1,arr2=arr.split(4)
print(arr1," ",arr2)
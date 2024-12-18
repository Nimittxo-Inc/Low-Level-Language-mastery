if (index >= 0 && index <= list->size || list->size < MAX_SIZE)
    {
        for (int i = list->size; i > index; i--)
        {
            list->data[i] = list->data[i - 1];
        }
        list->data[index] = value;
        list->size++;
    }
    else
    {
        printf("Index out of range or list is full.\n");
    }
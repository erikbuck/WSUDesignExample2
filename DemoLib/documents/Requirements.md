@page Requirements Requirements
# Requirements

@anchor R1_0 1.0 WSUWord shall store a string of text.

@anchor R1_1 1.1 The stored string of text shall be of length zero or more characters. 

@anchor R1_2 1.2 WSUWord shall provide a mechanism for users to append a single character to a stored string.

@anchor R1_3 1.3 WSUWord shall provide a mechanism for users to insert a single character into a stored string at a user specified index within the stored string.

@anchor R1_3_1 1.3.1 When a character is inserted into a stored string at an index, WSUWord shall retain all characters already in the stored string.

@anchor R1_3_2 1.3.2 When a character is inserted into a stored string at an index, all characters already in the stored string at indexes greater than or equal to the insertion index shall have their index positions within the string increased by one.

@anchor R1_4 1.4 WSUWord shall provide a mechanism for users to remove a the stored character at a user specified index within the stored string.

@anchor R1_4_1 1.4.1 When a character at an index within a stored string is removed, WSUWord shall retain all other characters already in the stored string.

@anchor R1_4_2 1.4.2 When a character at an index  within a stored string is removed, all characters already in the stored string at indexes greater than the removal index shall have their index positions within the string decreased by one.

@anchor R1_5 1.5 WSUWord shall provide a mechanism for users to insert a string of one or more characters at a user specified index within the stored string.

@anchor R1_5_1 1.5.1 When a string is inserted into a stored string at an index, WSUWord shall retain all characters already in the stored string.

@anchor R1_5_2 1.5.2 When a string is inserted into a stored string at an index, all characters already in the stored string at indexes greater than or equal to the insertion index shall have their index positions within the string increased by the length in characters of the inserted string.

@anchor R2_0 2.0 WSUWord shall provide a mechanism for users to undo the most recent modification performed upon the stored string.

@anchor R2_1 2.1 After an undo operation, the modification if any that preceded the undo operation shall become the most recent modification for the purpose of subsequent undo operations.

@anchor R2_2 2.2 WSUWord shall provide a mechanism for users to redo the most recent modification that was undone.

@anchor R2_3 2.3 After a redo operation, the next most recent modification that was undone shall be considered the most recent modification that was undone for the purpose of subsequent redo operations.

@anchor R2_4 2.4 After a redo operation, the redone modification shall become the most recent modification upon the string for the purpose of subsequent undo operations.

@anchor R2_5 2.5 WSUWord shall provide a mechanism to group multiple modifications to the stored string.

@anchor R2_5_1 2.5.1 Group of modifications shall be considered a single modification for the purposes of subsequent undo.

@anchor R2_5_2 2.5.2 Group of modifications that is undone shall be considered a single modification for the purposes of subsequent redo.

@anchor R2_5_3 2.5.3 Group of modifications that is redone shall be considered a single modification for the purposes of subsequent undo.

@anchor R3_0 3.0 WSUWord shall provide a mechanism to perform a sequence of modifications to the stored string.

@anchor R3_1 3.1 A sequence of operations will be considered a "script".

@anchor R3_1_1 3.1.1 Scripts shall be human readable

@anchor R3_2 3.2 A "script" will consist of one or more strings that describe modifications to be performed to the stored string.

@anchor R4_0 4.0 WSUWord shall provide a mechanism to output the stored string in a human readable format.

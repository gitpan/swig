
% Load our module
example

% Now try a few things

disp(example('get_time'))

disp('Computing some factorials')
for i = 1:10
    disp(example('fact',i))
end

disp('Printing some constants')

disp(PI)
disp(FOO)
disp(NAME)

disp('Manipulating some variables')

example('intvar_set',17)
a = example('intvar_get')

example('charvar_set', 'this is a test')
b = example('charvar_get')

% Test out some array manipulation functions

% Create a C array (like a malloc).  Returns a pointer.
ptr = example('double_array',20)

% Populate it with values
for i = 0:19
    example('double_set',ptr,i,sin(i));
end

% Extract the values

for i = 0:19
    disp(example('double_get',ptr,i));
end

%destroy it
example('double_destroy',ptr)




function [x1, y1, x2, y2] = readDataFromFiles(filePath)

file = dir(filePath); % 读取 filePath 下的所有文件和文件夹
file = {file(1:size(file)).name};
file(ismember(file, {'.','..'})) = []; % 删除 '.' 和 '..' 子目录
x1 = [];
x2 = [];

for i = 1:size(file, 2)
    data = double(textread([filePath, '/', file{i}], '%c') - '0');
    
    if file{i}(1) == '1'
        x1 = cat(2, x1, data(:));
    elseif file{i}(1) == '9'
        x2 = cat(2, x2, data(:));
    end
end

y1 = ones(1, size(x1, 2));
y2 = -ones(1, size(x2, 2));

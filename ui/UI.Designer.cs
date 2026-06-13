using Sonora;

namespace App;
partial class UI
{
    private System.ComponentModel.IContainer components = null;
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null)) components.Dispose();
        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code
    private void InitializeComponent()
    {
        components = new System.ComponentModel.Container();
        panel1 = new Panel();
        tableLayoutPanel1 = new TableLayoutPanel();
        label2 = new Label();
        deviceSelector = new ComboBox();
        label1 = new Label();
        label_SampleSize = new Label();
        flowLayoutPanel1 = new FlowLayoutPanel();
        radioButton1 = new RadioButton();
        radioButton2 = new RadioButton();
        radioButton3 = new RadioButton();
        radioButton4 = new RadioButton();
        maskedTextBox1 = new MaskedTextBox();
        button1 = new Button();
        contextMenuStrip1 = new ContextMenuStrip(components);
        panel1.SuspendLayout();
        tableLayoutPanel1.SuspendLayout();
        flowLayoutPanel1.SuspendLayout();
        SuspendLayout();
        // 
        // panel1
        // 
        panel1.Controls.Add(tableLayoutPanel1);
        panel1.Controls.Add(button1);
        panel1.Dock = DockStyle.Fill;
        panel1.Location = new Point(0, 0);
        panel1.Name = "panel1";
        panel1.Size = new Size(871, 639);
        panel1.TabIndex = 0;
        // 
        // tableLayoutPanel1
        // 
        tableLayoutPanel1.ColumnCount = 2;
        tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle());
        tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
        tableLayoutPanel1.Controls.Add(label2, 0, 2);
        tableLayoutPanel1.Controls.Add(deviceSelector, 1, 0);
        tableLayoutPanel1.Controls.Add(label1, 0, 0);
        tableLayoutPanel1.Controls.Add(label_SampleSize, 0, 1);
        tableLayoutPanel1.Controls.Add(flowLayoutPanel1, 1, 1);
        tableLayoutPanel1.Controls.Add(maskedTextBox1, 1, 2);
        tableLayoutPanel1.Location = new Point(12, 12);
        tableLayoutPanel1.Name = "tableLayoutPanel1";
        tableLayoutPanel1.RowCount = 3;
        tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
        tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
        tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
        tableLayoutPanel1.Size = new Size(545, 133);
        tableLayoutPanel1.TabIndex = 7;
        tableLayoutPanel1.Paint += tableLayoutPanel1_Paint;
        // 
        // label2
        // 
        label2.AutoSize = true;
        label2.Location = new Point(3, 88);
        label2.Name = "label2";
        label2.Size = new Size(106, 25);
        label2.TabIndex = 8;
        label2.Text = "Sample rate";
        // 
        // deviceSelector
        // 
        deviceSelector.DropDownStyle = ComboBoxStyle.DropDownList;
        deviceSelector.Location = new Point(132, 3);
        deviceSelector.Name = "deviceSelector";
        deviceSelector.Size = new Size(410, 33);
        deviceSelector.TabIndex = 2;
        deviceSelector.SelectionChangeCommitted += OnDeviceSelectCommit;
        // 
        // label1
        // 
        label1.AutoSize = true;
        label1.Location = new Point(3, 0);
        label1.Name = "label1";
        label1.Size = new Size(123, 25);
        label1.TabIndex = 0;
        label1.Text = "Audio devices";
        label1.Click += label1_Click_3;
        // 
        // label_SampleSize
        // 
        label_SampleSize.AutoSize = true;
        label_SampleSize.Location = new Point(3, 44);
        label_SampleSize.Name = "label_SampleSize";
        label_SampleSize.Size = new Size(105, 25);
        label_SampleSize.TabIndex = 5;
        label_SampleSize.Text = "Sample size";
        label_SampleSize.TextAlign = ContentAlignment.MiddleRight;
        label_SampleSize.Click += label2_Click;
        // 
        // flowLayoutPanel1
        // 
        flowLayoutPanel1.Controls.Add(radioButton1);
        flowLayoutPanel1.Controls.Add(radioButton2);
        flowLayoutPanel1.Controls.Add(radioButton3);
        flowLayoutPanel1.Controls.Add(radioButton4);
        flowLayoutPanel1.Location = new Point(132, 47);
        flowLayoutPanel1.Name = "flowLayoutPanel1";
        flowLayoutPanel1.Size = new Size(410, 38);
        flowLayoutPanel1.TabIndex = 2;
        // 
        // radioButton1
        // 
        radioButton1.AutoSize = true;
        radioButton1.Location = new Point(3, 3);
        radioButton1.Name = "radioButton1";
        radioButton1.Size = new Size(81, 29);
        radioButton1.TabIndex = 4;
        radioButton1.Text = "8 bits";
        radioButton1.UseVisualStyleBackColor = true;
        radioButton1.CheckedChanged += radioButton1_CheckedChanged;
        // 
        // radioButton2
        // 
        radioButton2.AutoSize = true;
        radioButton2.Checked = true;
        radioButton2.Location = new Point(90, 3);
        radioButton2.Name = "radioButton2";
        radioButton2.Size = new Size(91, 29);
        radioButton2.TabIndex = 6;
        radioButton2.TabStop = true;
        radioButton2.Text = "16 bits";
        radioButton2.UseVisualStyleBackColor = true;
        // 
        // radioButton3
        // 
        radioButton3.AutoSize = true;
        radioButton3.Location = new Point(187, 3);
        radioButton3.Name = "radioButton3";
        radioButton3.Size = new Size(91, 29);
        radioButton3.TabIndex = 7;
        radioButton3.Text = "24 bits";
        radioButton3.UseVisualStyleBackColor = true;
        radioButton3.CheckedChanged += radioButton3_CheckedChanged;
        // 
        // radioButton4
        // 
        radioButton4.AutoSize = true;
        radioButton4.Location = new Point(284, 3);
        radioButton4.Name = "radioButton4";
        radioButton4.Size = new Size(91, 29);
        radioButton4.TabIndex = 8;
        radioButton4.Text = "32 bits";
        radioButton4.UseVisualStyleBackColor = true;
        radioButton4.CheckedChanged += radioButton4_CheckedChanged;
        // 
        // maskedTextBox1
        // 
        maskedTextBox1.Location = new Point(132, 91);
        maskedTextBox1.Mask = "00000";
        maskedTextBox1.Name = "maskedTextBox1";
        maskedTextBox1.Size = new Size(107, 31);
        maskedTextBox1.TabIndex = 9;
        maskedTextBox1.ValidatingType = typeof(int);
        // 
        // button1
        // 
        button1.Location = new Point(563, 29);
        button1.Name = "button1";
        button1.Size = new Size(285, 94);
        button1.TabIndex = 3;
        button1.Text = "Play";
        button1.UseVisualStyleBackColor = true;
        button1.Click += button1_Click_1;
        // 
        // contextMenuStrip1
        // 
        contextMenuStrip1.ImageScalingSize = new Size(24, 24);
        contextMenuStrip1.Name = "contextMenuStrip1";
        contextMenuStrip1.Size = new Size(61, 4);
        // 
        // UI
        // 
        AutoScaleDimensions = new SizeF(10F, 25F);
        AutoScaleMode = AutoScaleMode.Font;
        ClientSize = new Size(871, 639);
        Controls.Add(panel1);
        Name = "UI";
        Text = "Audio";
        Load += Form1_Load;
        panel1.ResumeLayout(false);
        tableLayoutPanel1.ResumeLayout(false);
        tableLayoutPanel1.PerformLayout();
        flowLayoutPanel1.ResumeLayout(false);
        flowLayoutPanel1.PerformLayout();
        ResumeLayout(false);
    }

    #endregion

    private Panel panel1;
    private ContextMenuStrip contextMenuStrip1;
    private FlowLayoutPanel flowLayoutPanel1;
    private Label label1;
    private void DevicesIntoCombo()
    {
        string[] devices = Sonora.SoundWizard.GetDevices();
        if (devices.Length > 0)
        {
            deviceSelector.Items.AddRange(devices);
            deviceSelector.SelectedIndex = 0;
        }
        else
        {
            deviceSelector.Items.Add("No audio devices found");
            deviceSelector.SelectedIndex = 0;
            deviceSelector.Enabled = false;
        }
    }
    private ComboBox deviceSelector;
    private Button button1;
    private RadioButton radioButton1;
    private Label label_SampleSize;
    private RadioButton radioButton2;
    private RadioButton radioButton3;
    private RadioButton radioButton4;
    private TableLayoutPanel tableLayoutPanel1;
    private Label label2;
    private MaskedTextBox maskedTextBox1;
}
